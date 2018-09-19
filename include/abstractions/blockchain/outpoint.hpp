#ifndef ABSTRACTIONS_BLOCKCHAIN_OUTPOINT_HPP
#define ABSTRACTIONS_BLOCKCHAIN_OUTPOINT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
        
    template <typename digest>
    struct outpoint {
        digest Digest;
        N Index;
        
        outpoint(digest d, N i) : Digest(d), Index(i) {}
    };
    
} 

#endif
