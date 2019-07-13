#ifndef ABSTRACTIONS_BITCOIN_CACHED_MERKLE_HPP
#define ABSTRACTIONS_BITCOIN_CACHED_MERKLE_HPP

#include <abstractions/bitcoin/merkle.hpp>

namespace abstractions 
{
    
    namespace bitcoin {
    
        namespace header {
            
            // an implementation of the merkle tree that caches value. 
            template <typename digest, typename tree, typename list>
            struct cached {
                tree Merkle;
                
                const digest root() const {
                    if (Root == digest{}) Root = Merkle.root();
                    
                    return Root;
                }
                
                inline const bool contains(digest tx) const {
                    if (Leaves == list{}) Leaves = Merkle.leaves();
                    
                    return Leaves.contains(tx);
                }
                
            private:
                mutable digest Root;
                
                mutable list Leaves;
            };
            
        } 
    
    }

}

#endif
