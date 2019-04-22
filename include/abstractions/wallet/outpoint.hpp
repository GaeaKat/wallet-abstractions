#ifndef ABSTRACTIONS_WALLET_OUTPOINT
#define ABSTRACTIONS_WALLET_OUTPOINT

#include "txid.hpp"
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct outpoint {
            txid Transaction;
            index Index;
        };

    }

}

#endif
