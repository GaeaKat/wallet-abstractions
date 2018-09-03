#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    
    namespace header
    {
        
        template <typename tag, typename header>
        using merkle_root = tag (*const)(header);
            
        template <typename tag, typename header>
        using parent = tag (*const)(header);
        
    }
    
} 

#endif
