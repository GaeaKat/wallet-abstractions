#ifndef ABSTRACTIONS_REDEEM_RIGHTS_HPP
#define ABSTRACTIONS_REDEEM_RIGHTS_HPP

#include "mind.hpp"
#include <abstractions/database.hpp>
#include <abstractions/claim.hpp>
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
        
        template <typename secret, typename script, typename outpoint, typename output>
        using sign = thought<script, outpoint, output> (*)(secret);
        
        template<typename function, typename secret, typename script, typename outpoint, typename output>
        struct right {
            using thought = thought<script, outpoint, output>;
            
            // The power used to alienate this right. 
            sign<secret, script, outpoint, output> Power;
            
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
        
            right(
                sign<secret, script, outpoint> power, 
                satisfies<function, secret>& existence, 
                secret magic, 
                function f,
                knowledge claim)
                : Existence(existence(magic, f, claim) ? existence : nullptr),
                    Power(power), Secret(magic), Function(f), Claim(claim) {}
        };
        
        template<typename function, typename secret, typename script, typename outpoint>
        struct individual : public right<function, secret, script, outpoint> {
            using right = right<function, secret, script, outpoint>;
            using thought = thought<script, outpoint>;
            
            individual(
                sign<secret, script, outpoint> power, 
                satisfies<secret, script>& existence, 
                secret magic, 
                function f,
                knowledge claim) : right(existence, power, magic, f, claim) {}
        };
        
        template<typename function, typename secret, typename script, typename outpoint>
        struct collective : public right<function, vector<secret>, script, outpoint> {
            using right = right<function, vector<secret>, script, outpoint>;
            using thought = thought<script, outpoint>;
            
            const pointer<right> mine(vector<tag> tags, knowledge truth) const {
                throw 0;
            };
            
            collective(
                satisfies<vector<secret>, script>& existence, 
                sign<vector<secret>, script, outpoint> power, 
                secret magic, 
                function f,
                knowledge claim) : right(existence, power, magic, f, claim) {}
        };
        
        /*template<typename function, typename secret, typename script, typename outpoint, typename tag, typename will>
        struct memory : association<script, outpoint, tag, will> {
            using right = right<function, secret, script, outpoint>;
            
            const pointer<right> mine(vector<tag> tags, knowledge truth) const {
                throw 0;
            };
            
            thought<script, outpoint> realize(vector<tag> tags, knowledge truth) const final override {
                pointer<right> p = mine(tags, truth);
                if (p == nullptr) return nullptr;
                return p->Power(p->Secret);
            };
        };*/
    }
}

#endif
