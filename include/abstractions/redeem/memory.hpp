#ifndef ABSTRACTIONS_REDEEM_MEMORY_HPP
#define ABSTRACTIONS_REDEEM_MEMORY_HPP

#include "mind.hpp"

namespace abstractions 
{
    namespace redeem
    {
        /*template<typename function, typename will>
        struct memory {
            bool remember(function, will) const = 0;
        };*/
        
        template<typename power, typename function>
        struct satisfies {
            bool operator()(function, power, knowledge) const = 0;
        };
        
        template<typename power, typename function, typename will>
        struct posession {
            // A power exists that will cause this function to return true.
            const satisfies<power, function> Existence;
            
            power Power;
            
            function Function;
            
            knowledge Claim;
            
            bool valid() const {
                return Existence != nullptr;
            }
        
            posession(
                satisfies<power, function> existence, 
                power magic, 
                function output,
                knowledge claim) : Existence(existence(magic, output, claim) ? existence : nullptr), Power(magic), Function(output), Claim(claim) {}
        };
        
        template<typename power, typename function, typename input_script, typename outpoint, typename will>
        struct memory : association<input_script, outpoint, will> {
            // A power exists that will cause this function to return true.
            const satisfies<power, function> Existence;
            
            power Power;
            
            function Function;
            
            knowledge Claim;
            
            bool valid() const {
                return Existence != nullptr;
            }
            
            word<input_script, outpoint>* operator()(outpoint, will, knowledge) const = 0;
        
            memory(
                satisfies<power, function> existence, 
                power magic, 
                function output,
                knowledge claim) : Existence(existence(magic, output, claim) ? existence : nullptr), Power(magic), Function(output), Claim(claim) {}
        };
    }
}

#endif
