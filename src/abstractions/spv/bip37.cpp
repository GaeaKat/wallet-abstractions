#include <abstractions/spv/bip37.hpp>
#include <abstractions/data.hpp>

namespace abstractions {

    namespace merkle {

        struct bitstream {
            const bytestring& Data;
            bool read_bit(bool& b) {
                if (location >= Data.size()) return false;
                b = Data[location / 8] << (location % 8) & 1;
                location ++;
                return true;
            }

            bool read_digest(std::array<byte, digest_size>& d) {
                if (location + digest_size >= Data.size()) return false;
                int x = location / 8;
                int y = location % 8;

                // Need a special case here because otherwise we would read off the end of Data
                // in the case of a digest that was at the very end of the data structure. 
                if (y == 0) for (int i = 0; i < digest_size; i++) d[i] = Data[x + i];
                else for (int i = 0; i < digest_size; i++) {
                    d[i] = Data[x + i] << y;
                    d[i] += Data[x + i + 1] << (8 - y);
                }
                return true;
            }

            bitstream(bytestring& b) : Data(b), location(0) {}

        private: 
            uint16_t location;
        };
        
        node<digest>* make_node(
            // the stream we are reading from. 
            bitstream b,
            // we have to keep track of where we are in the merkle tree. 
            N size,
            N height,
            N depth,
            // the data we're collecting from the tree.
            list<digest>& Hashes,
            list<leaf<digest>>& Leaves,
            list<branch<digest>>& Branches,
            list<odd_branch<digest>>& OddBranches,
            list<digest&>& Transactions) {

            // first read a bit. 
            bool keep_going;
            if (!b.read_bit(keep_going)) return nullptr;
            
            // 0 means read a hash from this hash's list and return it as a leaf node
            // of the partial tree (not necessarily of the Merkle tree that it represents)
            if (!keep_going) {
                digest d;
                if (!b.read_digest(d)) return nullptr;
                Hashes = Hashes + d;
                leaf<digest> l(Hashes.first());
                Leaves = Leaves + l;
                return &(Leaves->First);
            }
            
            // is this a leaf node?
            bool leaf_node = depth == height;
            
            if (keep_going && !leaf_node) {
                node<digest>* right;
                
                // if size is 1, then this is a node with no left side. 
                if (size == 1) {
                    right = make_node(b, 1, height, depth +  1, Hashes, Leaves, Branches, OddBranches, Transactions);
                    if (right == nullptr) return nullptr;
                    odd_branch<digest> odd(*right);
                    OddBranches = OddBranches + odd;
                }
                
                // the size of the right part of the tree is the largest power of two smaller than the given size. 
                uint right_size = 1;
                while (right_size << 1 < size) right_size = right_size << 1;
                right = make_node(b, right_size, height, depth + 1, Hashes, Leaves, Branches, OddBranches, Transactions);
                if (right == nullptr) return nullptr;
                
                node<digest>* left = make_node(b, size - right_size, height, depth +  1, Hashes, Leaves, Branches, OddBranches, Transactions);
                if (left == nullptr) return nullptr;
                
                branch<digest> b(*right, *left);
            } 
        }
        
        node<digest>* root(
            bitstream b,
            N size, 
            list<digest>& Hashes,
            list<leaf<digest>>& Leaves,
            list<branch<digest>>& Branches,
            list<odd_branch<digest>> OddBranches,
            list<digest&>& Transactions) {

            if (size == 0) return nullptr;

            // The height is the greatest power p such that 2^p >= size
            int height = 1;
            int pow = 1;
            while (pow < size) {
                pow <<= 1;
                height++;
            }

            return make_node(b, size, height, 1, Hashes, Leaves, Branches, OddBranches, Transactions);
        }
        
        partial<digest> parse_partial(N size, bytestring b) {
            list<digest> Hashes{};
            list<leaf<digest>> Leaves{};
            list<branch<digest>> Branches{};
            list<odd_branch<digest>> OddBranches{};
            list<digest&> Transactions{};

            node<digest>* Root = root(bitstream(b), size, Hashes, Leaves, Branches, OddBranches, Transactions);

            if (Root == nullptr) return partial<digest>{};

            return partial<digest>{Hashes, Leaves, Branches, OddBranches, Transactions, Root};
        }

    }

}
