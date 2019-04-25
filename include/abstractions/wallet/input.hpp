// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_INPUT
#define ABSTRACTIONS_WALLET_INPUT

#include "script.hpp"
#include "outpoint.hpp"
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        using input = abstractions::input<outpoint, script>;
        
    }
    
} 

#endif
