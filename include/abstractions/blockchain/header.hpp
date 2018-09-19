#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/one_way.hpp>

namespace abstractions 
{
    
    namespace header
    {
        
        template <typename hdr, typename tag>
        using merkle_root = tag (*const)(hdr);
        
        template <typename hdr, typename tag>
        using hash = one_way<hdr, tag>;
            
        template <typename hdr, typename tag>
        using parent = tag (*const)(hdr);
        
    }
    
} 

#endif
