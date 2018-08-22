#ifndef ABSTRACTIONS_REDEEM_RIGHTS_HPP
#define ABSTRACTIONS_REDEEM_RIGHTS_HPP

#include "mind.hpp"
#include "observe.hpp"
#include "could.hpp"

namespace abstractions 
{
    namespace redeem
    {
        // satisfies says whether a give
        template<typename function, typename argument>
        struct satisfies {
            bool operator()(function, argument, knowledge) const = 0;
        };
        
        template <typename secret, typename input_script, typename outpoint>
        using sign = thought<input_script, outpoint> (*)(secret);
        
        template<typename function, typename secret, typename script, typename outpoint>
        struct right {
            using thought = thought<script, outpoint>;
            
            // The power used to alienate this right. 
            sign<secret, script, outpoint> Power;
            
            // A function which must return a particular value in order
            // for the right to be alienated. 
            function Function;
            
            // Values which the aformenentioned function must return in
            // order to use this right in a particular way. 
            knowledge Claim;
            
            // A secret exists that will cause this function to return the correct value.
            const satisfies<function, secret>& Existence;
            
            // The aformentioned secret.
            secret Secret;
            
            bool valid() const {
                return Existence != nullptr;
            }
            
            thought alienate(accomplishment outcome, knowledge truth) const {
                if (truth != (truth | Claim[outcome])) return nullptr;
                
                return Power(right::Secret);
            };
        
            right(
                satisfies<function, secret>& existence, 
                sign<secret, script, outpoint> power, 
                secret magic, 
                function output,
                knowledge claim)
                : Existence(existence(magic, output, claim) ? existence : nullptr),
                    Power(power), Secret(magic), Function(output), Claim(claim) {}
        };
        
        template<typename function, typename secret, typename script, typename outpoint, typename tag, typename will>
        struct memory : association<script, outpoint, tag, will> {
            using posession = right<function, secret, script, outpoint>;
            
            const pointer<posession> mine(outpoint) const = 0;
            
            thought<script, outpoint> realize(outpoint o, will w, knowledge k) const final override {
                pointer<posession> p = mine(o);
                if (p == nullptr) return nullptr;
                return p->alienate(w, k);
            };
        };
    }
}

#endif
