#ifndef ABSTRACTIONS_WALLET_OUTPUT
#define ABSTRACTIONS_WALLET_OUTPUT

#include <abstractions/wallet/spendable.hpp>
#include <script.hpp>

namespace abstractions {
    
    namespace wallet {
        
        struct output {
            satoshi Amount;
            script Script;
        };

    }

}

#endif
