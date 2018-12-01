#ifndef ABSTRACTIONS_BLOCKCHAIN_CHAIN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_CHAIN_HPP

#include <abstractions/blockchain/header.hpp>
#include <abstractions/blockchain/merkle.hpp>

namespace abstractions 
{
    
    namespace block
    {
        
        template <typename H, typename list, typename digest>
        struct chain {
            N Height;
            
            digest Latest;
            
            list Blocks;
            
            chain() : Height{0}, Blocks{} {}
            
            const N height() const {
                return Height;
            }
            
            const H operator[](N n) const {
                if (n > Height) return H{};
                
                return Blocks[Height - n];
            };
            
            const N height(H h) const {
                return Blocks.position(h);
            }
            
            const bool contains(H h) const {
                return height(h) != aleph_0;
            }
            
        private:
            chain(N h, list l) : Height{h}, Blocks{l} {}
            
            static bool valid_to(N height, digest d, list a) {
                if (height == 0) return d == header::Genesis<digest>;
                
                if (empty(a)) return false;
                
                H top = first(a);
                
                return d == top.hash() && valid_to(height - 1, top.parent(), rest(a));
            }
            
        public:
            bool valid() const {
                return valid_to(Height, Latest, Blocks);
            } 
            
            chain operator+(H h) {
                if (h.parent() == Latest) return chain{};
                
                return chain{Height + 1, h.hash(), Blocks + h};
            }
            
        };
        
        template <typename block, typename digest, typename tree>
        using merkle_trees = association<block, merkle::root_proof<digest, tree> >;
        
        template <typename index, typename block>
        using blocks = association<index, block>;
        
        template <typename tx, typename block>
        using tx_to_block = association<tx, block>;

    }
    
} 

#endif
