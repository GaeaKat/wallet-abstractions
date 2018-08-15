#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template<typename power, typename function, typename knowledge>
        using satisfies = bool (*)(function, power, knowledge);
        
        template<typename power, typename function, typename knowledge, typename will, typename input_script, typename outpoint>
        struct word {
            // A power exists that will cause this function to return true.
            const satisfies<function, power, knowledge> Existence;
            
            power Power;
            
            bool valid() const {
                return Existence != nullptr;
            }
            
            thought<input_script, outpoint> speak(will);
            
            deed(function output, knowledge claim) : Existence(nullptr), posession<function, knowledge>(output, claim), Power(power) {}
            deed(
                satisfies<function, power, knowledge> existence, 
                power magic, 
                function output,
                knowledge claim) : Existence(existence(magic, output, claim) ? existence : nullptr), posession<function, knowledge>(output, claim), Power(power) {}
        };
    
    } // redeem
    
} // abstractions

#endif
