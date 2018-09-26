#include <abstractions/spv/bip37.hpp>

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
            N size, N height, N depth, bool right,
            bitstream b,
            list<digest>& Hashes,
            list<leaf<digest>>& Leaves,
            list<branch<digest>>& Branches,
            list<digest&>& Transactions) {

            bool keep_going;
            if (!b.read_bit(keep_going)) return nullptr;
            
            if (!keep_going) {
                digest d;
                if (!b.read_digest(d)) return nullptr;
                Hashes = Hashes + d;
                leaf<digest> l(Hashes.first());
                Leaves = Leaves + l;
                return ;
            }

            // is this a leaf node? 
            if (height == depth) {
                Hashes = Hashes + 
            }
        }
        
        node<digest>* root(
            N size, 
            bitstream b,
            list<digest>& Hashes,
            list<leaf<digest>>& Leaves,
            list<branch<digest>>& Branches,
            list<digest&>& Transactions) {

            if (size == 0) return nullptr;

            // The height is the greatest power p such that 2^p >= size
            int height = 1;
            int pow = 1;
            while (pow < size) {
                pow <<= 1;
                height++;
            }

            return make_node(size, height, 1, true, b, Hashes, Leaves, Branches, Transactions);
        }
        
        partial_tree<digest> parse_partial(N size, bytestring b) {
            list<digest> Hashes{};
            list<leaf<digest>> Leaves{};
            list<branch<digest>> Branches{};
            list<odd_branch<digest>> OddBranches{};
            list<digest&> Transactions{};

            node<digest>* Root = root(size, bitstream(b), Hashes, Leaves, Branches, Transactions);

            if (Root == nullptr) return partial_tree<digest>{};

            return partial_tree<digest>{Hashes, Leaves, Branches, OddBranches, Transactions, Root};
        }

    }

}
