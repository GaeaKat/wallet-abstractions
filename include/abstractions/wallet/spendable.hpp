// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_SPENDABLE
#define ABSTRACTIONS_WALLET_SPENDABLE

#include <abstractions/redeem/unspent.hpp>
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/input.hpp>
#include <abstractions/wallet/output.hpp>
#include <abstractions/pattern/pay_to_address.hpp>
#include <abstractions/pattern/pay_to_pubkey.hpp>

namespace abstractions::bitcoin {
    using transaction = abstractions::transaction<txid, script>;
    
    using redeemer = const abstractions::pattern::interface::redeemer<secret, script, transaction>*;
    using payable = const abstractions::pattern::interface::payable<pubkey, script>*;
    
    template <typename pk> 
    using pattern = const abstractions::pattern::interface::pattern<secret, pk, script, transaction>*;
    
    using unspent = redeem::unspent<script, txid, secret, pubkey>;
    using spendable = redeem::spendable<script, txid, secret, pubkey>;
    
    const auto pay_to_address_compressed =
        abstractions::pattern::pay_to_address<secret, pubkey, address, transaction>{};
    const auto pay_to_address_uncompressed =
        abstractions::pattern::pay_to_address<secret, uncompressed_pubkey, address, transaction>{};
    const auto pay_to_pubkey_compressed =
        abstractions::pattern::pay_to_pubkey<secret, pubkey, transaction>{};
    const auto pay_to_pubkey_uncompressed = 
        abstractions::pattern::pay_to_pubkey<secret, uncompressed_pubkey, transaction>{};
    
}

#endif 
