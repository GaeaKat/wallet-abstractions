#ifndef ABSTRACTIONS_BLOCKCHAIN_PROFILE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_PROFILE_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    
    namespace bitcoin
    {
    
        namespace profile
        {
            
            enum ticker : uint32_t {
                BTC = 0, 
                BCH = 1, 
                BSV = 2
            };
            
            enum attribute {
                p2sh,
                cashaddr, 
                slp
            };
            
            inline bool is(ticker t, attribute x) {
                if (x == p2sh) return t != BSV;
                if (x == cashaddr) return t == BCH;
                if (x == slp) return t != BTC;
                return false;
            }
            
            enum pattern : uint32_t {
                p2pkh = 4,
                p2pk = 8,
                multisig = 2,
                p2pkh_p2sh = 5,
                p2pk_p2sh = 9, 
                multisig_p2sh = 3
            };
            
            const uint32_t p2sh_bit = 1;
            const uint32_t multisig_bit = 2;
            
            inline bool is_p2sh(pattern p) {
                return ((p & p2sh_bit) == 1);
            }
            
            inline bool is_multisig(pattern p) {
                return ((p & multisig_bit) == 1);
            }
            
            inline bool supports(ticker t, pattern p) {
                if (t == BSV) return !is_p2sh(p);
                return true;
            }
        
        }
    
    }
    
} 

#endif

