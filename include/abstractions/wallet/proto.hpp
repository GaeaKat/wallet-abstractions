// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_PROTO
#define ABSTRACTIONS_WALLET_PROTO

#include <abstractions/wallet.hpp>
#include "keys.hpp"
#include "address.hpp"
#include "transaction.hpp"
#include "outpoint.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        template <typename machine> 
        using proto = abstractions::wallet<secret, address, script, output, outpoint, transaction, machine> ;
        
        extern const satoshi dust;

    }

}

#endif
