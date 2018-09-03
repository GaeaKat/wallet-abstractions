#ifndef ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions
{
        
    namespace merkle
    {
            
        template <typename tag>
        using combine = tag (*const)(tag, tag);
            
        template <typename tag>
        struct node {
            pointer<node> Next;
            tag Left;
            tag Right;
        };
            
        template <typename tag>
        using proof = list<node<tag>>;
            
        template <typename tag>
        bool verify(combine<tag> combine, proof<tag> next, tag i, tag f) {
            if (next == nullptr) return i == f;
                
            if (i != next->Left && i != next->Right) return false;
                
            return verify(combine, next->Next, combine(next->Left, next->Right), f);
        }
        
    }

}

#endif
