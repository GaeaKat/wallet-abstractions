// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_ACCOUNT_OUTPOINT
#define ABSTRACTIONS_ACCOUNT_OUTPOINT

#include <abstractions/transaction.hpp>
#include <abstractions/wallet/txid.hpp>

namespace abstractions {
    
    namespace account {
        
        using outpoint = abstractions::outpoint<bitcoin::txid>;
        
    }
    
} 

#endif

