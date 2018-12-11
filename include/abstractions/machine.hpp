#ifndef ABSTRACTIONS_MACHINE_HPP
#define ABSTRACTIONS_MACHINE_HPP

#include <abstractions/blockchain/script.hpp>
#include <abstractions/blockchain/transaction.hpp>

namespace abstractions
{

    namespace machine 
    {

        namespace definition 
        {

            template <typename M, typename script>
            struct all_signatures_succeed {
                // This means run without really checking signature operations. 
                bool run(script input, script output) {
                    return M{input, output}.ErrorCode != 0;
                }
            };

            template <typename M, typename script, typename tx>
            struct for_real {
                // This means run checking sigops on the given tx. 
                bool run(scripts::input_index<tx> t, script input, script output) {
                    return M{t, input, output}.ErrorCode != 0;
                }
            };

        }
        
        template <typename M, typename script>
        inline bool run(script input, script output) {
            return definition::all_signatures_succeed<M, script>{}.run(input, output);
        }
        
        template <typename M, typename script, typename tx>
        inline bool run(scripts::input_index<tx> t, script input, script output) {
            return definition::for_real<M, script, tx>{}.run(t, input, output);
        }
        
        template <typename M, typename script, typename tx>
        inline bool run(scripts::input_index<tx> t, script output) {
            return definition::for_real<M, script, tx>{}.run(t, transaction::inputs(t.Transaction)[t.Index], output);
        }
        
    }
    
}

#endif

