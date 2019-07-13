// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_BITCOIN_OUTPUT
#define ABSTRACTIONS_BITCOIN_OUTPUT

#include <abstractions/abstractions.hpp>

namespace abstractions::timechain::output {
    
    template <typename output, typename ops>
    struct interface {
    
        // How much is stored in a given output?
        static satoshi value(output o) {
            return o.value();
        }
            
        // What is the script defining how this output is redeemed. 
        static ops script(output o) {
            return o.script();
        }
        
    };
    
    // How much is stored in a given output?
    template <typename output, typename ops>
    inline satoshi value(output o) {
        return interface<output, ops>::value(o);
    }
            
    // What is the script defining how this output is redeemed. 
    template <typename output, typename ops>
    inline ops script(output o) {
        return interface<output, ops>::script(o);
    }
    
} 

#endif
