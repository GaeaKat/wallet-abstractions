// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_PROTO
#define ABSTRACTIONS_WALLET_PROTO

#include <abstractions/wallet.hpp>
#include "keys.hpp"
#include "address.hpp"
#include "transaction.hpp"
#include "outpoint.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        template <typename machine, typename script> 
        using proto = abstractions::wallet<secret, address, script, output<script>, outpoint, transaction<script>, machine> ;
        
        extern const satoshi dust;

    }

}

#endif
