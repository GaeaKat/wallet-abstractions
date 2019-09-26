// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_OUTPOINT
#define ABSTRACTIONS_WALLET_OUTPOINT

#include <abstractions/abstractions.hpp>
#include <abstractions/transaction.hpp>
#include "txid.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using outpoint = abstractions::outpoint<txid>;

    }

}

#endif
