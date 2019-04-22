#ifndef ABSTRACTIONS_WALLET_OUTPUT
#define ABSTRACTIONS_WALLET_OUTPUT

#include <abstractions/abstractions.hpp>
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct output {
            satoshi Amount;
            script ScriptPubKey;
        };

    }

}

#endif
