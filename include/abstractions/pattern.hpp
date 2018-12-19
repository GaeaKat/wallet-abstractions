#ifndef ABSTRACTIONS_PATTERN_HPP
#define ABSTRACTIONS_PATTERN_HPP

#include <abstractions/claim.hpp>
#include <abstractions/data.hpp>
#include <abstractions/data/map.hpp>
#include <abstractions/tags.hpp>

namespace abstractions 
{
    
    namespace patterns
    {

        template <typename script, typename machine>
        struct verify_script {
            struct predicate {
                script Input;
                machine Machine;
            };
            
            verify_script() {}
            
            bool operator()(script output, predicate p) {
                return script::run(p.Machine, p.Input, output);
            }
        };
        
        template <typename machine, typename script>
        using verifyable_claim = claim<verify_script<machine, script>, script, typename verify_script<machine, script>::predicate>;
        
        template <typename machine, typename script>
        using verifyable_proof = proof<verify_script<machine, script>, script, typename verify_script<machine, script>::predicate>;
        
        template <typename pattern, typename script, typename keys, typename tx_i, typename machine>
        struct redeem_script {
            struct subject {
                script Output;
                pattern Pattern;
                
                subject(script o, pattern p) : Output{o}, Pattern{p} {}
            };
            
            struct predicate {
                keys Keypair;
                tx_i Index;
                machine Machine;
                
                predicate(keys k, tx_i i, machine m) : Keypair{k}, Index{i}, Machine{m} {}
            };
            
            bool operator() (subject s, predicate p) {
                return verify_script<machine, script>{}(s.Output, typename verify_script<machine, script>::predicate{s.Pattern.MakeInput(p.Index, p.Keypair.Secret), p.Machine});
            }
        };
    
        template <typename pattern, typename script, typename keys, typename tx_i, typename machine>
        using redeemable_claim = claim<redeem_script<machine, script, keys, tx_i, machine>,
            typename redeem_script<machine, script, keys, tx_i, machine>::subject,
            typename redeem_script<machine, script, keys, tx_i, machine>::predicate>;
        
        template <typename pattern, typename script, typename keys, typename tx_i, typename machine>
        using redeemable_proof = proof<redeem_script<machine, script, keys, tx_i, machine>,
            typename redeem_script<machine, script, keys, tx_i, machine>::subject,
            typename redeem_script<machine, script, keys, tx_i, machine>::predicate>;
        
        // whether to take note of a given output. 
        template <typename pattern, typename script, typename keys, typename tx_i, typename machine, typename tag, typename keyset>
        redeemable_claim<pattern, script, keys, tx_i, machine> observe(list<pattern> patterns, script output, keyset k) {
            for (pattern p : patterns) if (p.match(output)) for (tag t : p.ReadTags(output)) if (k.contains(t))
                return redeemable_claim<pattern, script, keys, tx_i, machine>{
                    redeem_script<pattern, script, keys, tx_i, machine>{}, 
                    typename redeem_script<pattern, script, keys, tx_i, machine>::subject{output, p}};
            return {};
        }
        
        template <typename script, typename make_input, typename make_output, typename read>
        struct pattern {
            read ReadTags;
            
            bool match(script output) {
                return (!ReadTags(output).empty());
            }
            
            // a function that makes an output script given a public key. 
            make_output MakeOutput;
            
            // claim that 
            //    for all pubkey p and output o, match(MakeOutput(p), p). 
            
            make_input MakeInput;
            
            // claim that there exists a to_public tp and machine m such that
            //    for all secret s, pubkey p, and transaction t, 
            //        tp(s) == p  <==>  m.initialize(t) << MakeInput(t, s) << MakeOutput(p)
            
            template <typename tx_i, typename key>
            script redeem(tx_i t, key k) {
                return MakeInput(t, k);
            } 

        };
        
    }
    
    template <typename script, typename pattern, typename output, typename tx_i, typename key>
    script redeem(list<pattern> known, output prev, tx_i t, key k) {
        for (pattern essence : known) if (essence.match(prev.script())) return essence.redeem(prev.script(), t, k);
        return {};
    }
    
    template <typename truth, typename pattern, typename script, typename keys>
    truth observe(list<pattern> theory, script out, keys k) {        
        struct inner {
            script Out;
            
            truth operator()(pattern p) {
                return p.Observe(get_all(p.Read(out), k));
            }
        };
        
        return reduce(apply(inner{out}, theory));
    } 
    
} 

#endif

