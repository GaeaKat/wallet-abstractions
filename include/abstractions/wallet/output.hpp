#ifndef ABSTRACTIONS_WALLET_OUTPUT_HPP
#define ABSTRACTIONS_WALLET_OUTPUT_HPP

#include <abstractions/wallet/spendable.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using script = vector<byte>;
        
        struct output {
            satoshi Amount;
            script Script;
        };

    }

}

#endif
