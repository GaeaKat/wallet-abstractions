#ifndef ABSTRACTIONS_BLOCKCHAIN_CHAIN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_CHAIN_HPP

#include <abstractions/blockchain/header.hpp>

namespace abstractions 
{
    
    namespace block
    {
        
        template <typename chain, typename map> 
        N index(const chain c, map& m) {
            if (c == chain{}) {
                m = map{};
                return 0;
            };
            
            N height = index(rest(c), m) + 1;
            
            m = m.insert(height, first(c));
            
            return height;
        }
        
        template <typename index, typename digest>
        using merkle_trees = association<index, merkle::root_proof<digest> >;
        
        template <typename index, typename block>
        using blocks = association<index, block>;
        
        template <typename digest, typename A, typename T>
        struct chain : association<N, digest> {
            N Height;
            
            A Blocks;
            
            T Tree;
            
            const digest operator[](N n) const final override {
                return Blocks[n];
            };
            
        private:
            bool valid_to(N height, digest d) const {
                if (height == 0) return d == header::Genesis<digest>;
                
                digest b = Blocks[height];
                
                return d == b && valid_to(height - 1, header::parent(Tree[b]));
            }
            
        public:
            bool valid() const {
                if (Height == 0) return true;
                
                return valid_to(Height - 1, header::parent(Tree[Blocks[Height]]));
            } 
            
        };

    }
    
} 

#endif
