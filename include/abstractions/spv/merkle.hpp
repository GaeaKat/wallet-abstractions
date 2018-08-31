#ifndef ABSTRACTIONS_SPV_MERKLE_HPP
#define ABSTRACTIONS_SPV_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/blockchain.hpp>

namespace abstractions
{

    namespace spv
    {
        
        namespace merkle
        {
            
            template <typename hash>
            using combine = hash (*const)(hash, hash);
            
            template <typename hash>
            struct node {
                pointer<node> Next;
                hash Left;
                hash Right;
            };
            
            template <typename hash>
            bool verify(combine<hash> combine, pointer<node<hash>> next, hash i, hash f) {
                if (next == nullptr) return i == f;
                
                if (i != next->Left && i != next->Right) return false;
                
                return verify(combine, next->Next, combine(next->Left, next->Right), f);
            }
        
        }
        
    }

}

#endif
