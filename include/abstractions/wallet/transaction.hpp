// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_TRANSACTION
#define ABSTRACTIONS_WALLET_TRANSACTION

#include <abstractions/abstractions.hpp>
#include "input.hpp"
#include "output.hpp"
#include "txid.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct transaction : public abstractions::transaction<input, output> {
            txid hash() const;
            transaction(hex);
        };
        
    }

}

#endif
