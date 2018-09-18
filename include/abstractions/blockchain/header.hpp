#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/one_way.hpp>

namespace abstractions 
{
    
    namespace headers
    {
        
        template <typename header, typename tag>
        using merkle_root = tag (*const)(header);
        
        template <typename header, typename tag>
        using hash = one_way<header, tag>;
            
        template <typename header, typename tag>
        using parent = tag (*const)(header);
        
    }
    
} 

#endif
