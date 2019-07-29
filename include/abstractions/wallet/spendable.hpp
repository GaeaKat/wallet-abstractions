// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_SPENDABLE
#define ABSTRACTIONS_WALLET_SPENDABLE

#include <abstractions/redeem.hpp>
#include <abstractions/wallet/transaction.hpp>

namespace abstractions::bitcoin {

    using redeemer = abstractions::pattern::abstract::redeemer<const secret&, const script,
        const abstractions::transaction<input, output>&>&;
    using pattern = abstractions::pattern::abstract::pattern<const secret&, const script,
        const abstractions::transaction<input, output>&>&;
    
    using vertex = vertex<const secret&, const script, txid>;
    using spendable = vertex::spendable;
    
}

#endif 
