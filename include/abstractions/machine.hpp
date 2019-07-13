// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_MACHINE
#define ABSTRACTIONS_MACHINE

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace machine {
    
        // template specialize this if you have a different
        // definition of how the machine is run. 
        template <typename interpreter, typename script, typename tx>
        struct run {
            bool operator()(script output, script input, tx transaction, index i, satoshi amount) const {
                return interpreter{transaction, i, amount}.run(output, input);
            }
            
            bool operator()(script output, script input) const {
                return interpreter{}.run(output, input);
            }
        };
    
        template <typename interpreter, typename script, typename tx>
        struct definition {
            bool run(script output, script input, tx transaction, index i, satoshi amount) const {
                return machine::run<interpreter, script, tx>{}(output, input, transaction, i, amount);
            }
            
            bool run(script output, script input) const {
                return machine::run<interpreter, script, tx>{}(output, input);
            }
        };
    
    }

}

#endif

