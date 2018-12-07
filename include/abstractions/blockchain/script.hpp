#ifndef ABSTRACTIONS_BLOCKCHAIN_SCRIPT_HPP
#define ABSTRACTIONS_BLOCKCHAIN_SCRIPT_HPP

#include <abstractions/blockchain/transaction.hpp>
#include <abstractions/claim.hpp>

namespace abstractions 
{
    
    namespace script
    {
        
        // given a virtual machine, an output script, and a transaction index, 
        // check that the machine returns true for the script formed from the
        // denoted input followed by the output script. 
        template <typename machine, typename script>
        inline bool run(machine m, script input, script output) {
            return (m << input << output).valid_state();
        }
        
        // denotation of a given input to a given transaction. 
        template <typename tx>
        struct input_index {
            tx Transaction;
            N Index;
            
            bool valid() const {
                return Index != aleph_0 && Transaction != tx{};
            }
            
            input_index() : Index{aleph_0}, Transaction{} {}
            input_index(tx t, N i) : Transaction{t}, Index{i} {}
            
            template <typename s>
            s get_input_script() const {
                if (valid()) return transaction::inputs(Transaction)[Index];
                return s{};
            }
        };
        
        // given a virtual machine, an output script, and a transaction index, 
        // check that the machine returns true for the script formed from the
        // denoted input followed by the output script. 
        template <typename machine, typename script, typename tx>
        inline bool run(script output, input_index<tx> ti) {
            return run(machine{ti.Transaction}, ti.Transaction.inputs()[ti.Index].script(), output);
        }
        
        // define a function by a virtual machine which takes 
        // an output script and a transaction input index and returns
        // true based on whether the script has succeeded. 
        template <typename machine, typename script, typename tx>
        struct run_script {
            machine Machine;
            
            run_script(machine m) : Machine{m} {}
            
            bool operator()(script s, input_index<tx> ti) {
                return run(Machine, s, ti);
            }
        };
        
        // claim that a transaction input index exists such that the given
        // output is redeemed. 
        template <typename machine, typename script, typename tx>
        inline claim<run_script<machine, script, tx>, script, input_index<tx>> claim_redeemable(machine m, script s) {
            return claim<run_script<machine, script, tx>, script, input_index<tx>>{run_script<machine, script, tx>{m}, s};
        }
        
        // proove that a transaction input index redeems a given script. 
        template <typename machine, typename script, typename tx>
        inline proof<run_script<machine, script, tx>, script, input_index<tx>> prove_redeemable(machine m, script s, input_index<tx> ti) {
            return proof<run_script<machine, script, tx>, script, input_index<tx>>{claim_redeemable(m, s), ti};
        }
        
    }
    
} 

#endif
