#ifndef ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions
{
        
    namespace merkle
    {
            
        template <typename digest>
        using combine = digest (*const)(digest, digest);
            
        template <typename digest>
        struct node {
            pointer<node> Parent;
            digest Left;
            digest Right;
        };
            
        template <typename digest>
        using proof = list<node<digest>>;
            
        template <typename digest>
        bool verify(combine<digest> combine, proof<digest> next, digest i, digest f) {
            if (next == nullptr) return i == f;
                
            if (i != next->Left && i != next->Right) return false;
                
            return verify(combine, next->Next, combine(next->Left, next->Right), f);
        }
        
    }

}

#endif
