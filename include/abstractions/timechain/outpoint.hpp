// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_BITCOIN_OUTPOINT
#define ABSTRACTIONS_BITCOIN_OUTPOINT

#include <abstractions/abstractions.hpp>

namespace abstractions::timechain::outpoint {
    
    template <typename outpoint, typename digest, typename N>
    struct interface {

        // How much is stored in a given output?
        static digest reference(outpoint o) {
            return o.reference();
        }
            
        // What is the script defining how this output is redeemed. 
        static N index(outpoint o) {
            return o.index();
        }
    
    };
    
} 

#endif
