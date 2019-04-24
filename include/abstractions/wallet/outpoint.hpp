#ifndef ABSTRACTIONS_WALLET_OUTPOINT
#define ABSTRACTIONS_WALLET_OUTPOINT

#include "txid.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct outpoint {
            txid Transaction;
            index Index;
        };

    }

}

#endif
