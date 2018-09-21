#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/one_way.hpp>
#include <abstractions/data.hpp>

namespace abstractions 
{
    
    namespace header
    {
        
        template <typename hdr, typename tag>
        using merkle_root = tag (* const)(hdr);
        
        template <typename hdr, typename tag>
        using hash = one_way<hdr, tag>;
            
        template <typename hdr, typename tag>
        using parent = tag (* const)(hdr);
        
        template <typename hdr, typename N>
        using pow = N (* const)(hdr);
        
        template <typename hdr, typename N>
        N cumulative_pow(pow<hdr, N> p, list<hdr> lh) {
            N cpow = 0;
            
            for (list<hdr> ll = lh; ll != nullptr; ll = ll->Rest) cpow += p(ll->First);
            return cpow;
        }
        
    }
    
} 

#endif
