#ifndef ABSTRACTIONS_BLOCKCHAIN_PATTERN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_PATTERN_HPP

#include <abstractions/claim.hpp>
#include <abstractions/data.hpp>

namespace abstractions 
{
    
    namespace patterns {
        // define a function by a virtual machine which input and output
        // scripts and checks them, assuming signature operations
        // return true. 
        template <typename machine, typename script>
        struct check_script {
            machine Machine;
            
            check_script(machine m) : Machine{m} {}
            
            bool operator()(script input, script output) {
                return script::check(Machine, input, output);
            }
        };
        
        template<typename machine, typename script>
        using script_claim = claim<check_script<machine, script>, script, script>;
        
        template<typename machine, typename script>
        using script_proof = proof<check_script<machine, script>, script, script>;
        
        template <typename script, typename secret, typename pubkey, typename make_input, typename make_output, typename read_tags>
        struct pattern {
            read_tags ReadTags;
            
            bool match(script output) {
                return (!ReadTags(output).empty());
            }
            
            make_output MakeOutput;
            
            // claim that 
            //    for all pubkey p and output o, match(MakeOutput(p), p). 
            
            make_input MakeInput;
            
            // claim that there exists a to_public tp and machine m such that
            //    for all secret s, pubkey p, and transaction t, 
            //        tp(s) == p  <==>  m.initialize(t) << MakeInput(t, s) << MakeOutput(p)
            
            template <typename tx, typename keys>
            script redeem(script output, tx t, keys k) {
                return MakeInput(t, get_all(ReadTags(output), k));
            } 
            
        };
        
    }
    
    template <typename S, typename output, typename tx, typename pattern, typename keys>
    S redeem(output prev, tx t, list<pattern> known, keys k) {
        for (pattern essence : known) if (essence.match(prev.script())) return essence.redeem(prev.script(), t, k);
        return {};
    }
    
} 

#endif

