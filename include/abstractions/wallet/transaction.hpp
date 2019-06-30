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
        
        template <typename script>
        struct transaction : public abstractions::transaction<input<script>, output<script>> {
            txid hash() const;
            transaction(string hex);
            
            using representation = typename abstractions::transaction<input<script>, output<script>>::representation;
        };
        
    }

}

#endif
