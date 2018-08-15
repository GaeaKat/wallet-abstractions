#ifndef ABSTRACTIONS_REDEEM_MEMORY_HPP
#define ABSTRACTIONS_REDEEM_MEMORY_HPP

#include<abstractions/abstractions.hpp>

namespace abstractions 
{
    // redeem contains a high-level way of redeeming bitcoin txs.
    namespace redeem
    {
        template<typename function, typename will>
        struct memory {
            bool remember(function, will) const = 0;
        };
        
        template<typename power, typename function, typename knowledge>
        using satisfies = bool (*)(function, power, knowledge);
        
        template<typename function, typename knowledge>
        struct posession {            
            function Output;
                
            // truth claims concerning this output. 
            // (such as what information we have about it.) 
            // Also may contain an index as to how tho find that 
            // information. 
            knowledge Claim; 
            
            virtual bool valid() const {
                return true;
            };
        protected:
            posession(function output, knowledge claim) : Output(output), Claim(claim) {}
        };
        
        template<typename power, typename function, typename knowledge>
        struct deed : posession<function, knowledge> {
            // A power exists that will cause this function to return true.
            const satisfies<function, power, knowledge> Existence;
            
            bool valid() const {
                return Existence != nullptr;
            }
            
            deed(function output, knowledge claim) : Existence(nullptr), posession<function, knowledge>(output, claim) {}
            deed(
                satisfies<function, power, knowledge> existence, 
                power magic, 
                function output,
                knowledge claim) : Existence(existence(magic, output, claim) ? existence : nullptr), posession<function, knowledge>(output, claim) {}
        };
    }
}

#endif
