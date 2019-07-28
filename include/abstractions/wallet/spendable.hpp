// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_SPENDABLE
#define ABSTRACTIONS_WALLET_SPENDABLE

#include <abstractions/redeem.hpp>
#include <abstractions/wallet/transaction.hpp>

namespace abstractions::bitcoin {

    using redeemer = abstractions::pattern::abstract::redeemer<const secret&, const script, const transaction&>;
    using pattern = abstractions::pattern::abstract::pattern<const secret&, const script, const transaction&>;
    
    struct spendable : public vertex<const secret&, const script, txid>::spendable {
        using parent = vertex<const secret&, const script, txid>::spendable;
        redeemer& Redeemer;
        
        script redeem(const transaction& t, index i) const {
            return parent::redeem<const transaction&>(Redeemer, t, i);
        };
    };
    
}

#endif 
