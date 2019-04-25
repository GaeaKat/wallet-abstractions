// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_OUTPOINT
#define ABSTRACTIONS_WALLET_OUTPOINT

#include <abstractions/fundamental.hpp>
#include "txid.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using outpoint = abstractions::outpoint<txid>;

    }

}

#endif
