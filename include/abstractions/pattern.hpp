#ifndef ABSTRACTIONS_PATTERN_HPP
#define ABSTRACTIONS_PATTERN_HPP

#include <abstractions/claim.hpp>
#include <abstractions/data.hpp>
#include <abstractions/map.hpp>
#include <abstractions/tags.hpp>

namespace abstractions 
{
    
    namespace patterns
    {

        // define a function by a virtual machine which takes input and output
        // scripts and checks them. 
        template <typename machine, typename script>
        struct verify_script {
            machine Machine;
            
            verify_script(machine m) : Machine{m} {}
            
            bool operator()(script input, script output) {
                return script::run(Machine, input, output);
            }
        };
        
        template <typename machine, typename script>
        using redeemable_claim = claim<verify_script<machine, script>, script, script>;
        
        template <typename machine, typename script>
        using redeemable_proof = proof<verify_script<machine, script>, script, script>;
        
        // given a list of patterns, generate a redeemable_claim from 
        
        template <typename script, typename key, typename observe, typename make_input, typename make_output, typename read>
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
            
            template <typename tx_i>
            script redeem(script output, tx_i t, key k) {
                return MakeInput(t, Read(output), k);
            } 
            
            // should we observe an output of a given pattern and for what purpose? 
            observe Observe;

        };
        
    }
    
    template <typename script, typename pattern, typename output, typename tx_i, typename key>
    script redeem(list<pattern> known, output prev, tx_i t, key k) {
        for (pattern essence : known) if (essence.match(prev.script())) return essence.redeem(prev.script(), t, k);
        return {};
    }
    
    template <typename truth, typename pattern, typename script, typename keys>
    truth observe(list<pattern> theory, script out, keys k) {
        static const map::definition::map<Mtp, tag, inverse::proof<F, pubkey, tag>> r1{};
        
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

