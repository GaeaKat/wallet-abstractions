// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_OUTPUT
#define ABSTRACTIONS_WALLET_OUTPUT

#include <abstractions/transaction.hpp>
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using output = abstractions::output<script>;

    }

}

#endif
