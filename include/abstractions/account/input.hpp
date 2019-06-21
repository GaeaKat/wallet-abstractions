// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_ACCOUNT_INPUT
#define ABSTRACTIONS_ACCOUNT_INPUT

#include <abstractions/transaction.hpp>
#include "outpoint.hpp"

namespace abstractions {
    
    namespace account {
        
        template <typename script>
        using input = abstractions::input<outpoint, script>;
        
    }
    
} 

#endif

