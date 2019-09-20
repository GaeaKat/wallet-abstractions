// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_REDEEM
#define ABSTRACTIONS_REDEEM_REDEEM

#include <abstractions/pattern.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions::redeem {
    
    template <typename secret, typename pubkey, typename script, typename tx>
    using pattern = const typename pattern::interface::pattern<secret, pubkey, script, tx>*;
    
    template <typename script>
    using output = typename output<script>::representation;
    
    template <typename txid>
    using outpoint = typename outpoint<txid>::representation;
    
    template <typename txid, typename script>
    using input = typename input<txid, script>::representation;
    
    template <typename txid, typename script>
    using transaction = transaction<txid, script>;
    
} 

#endif
