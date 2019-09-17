// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_SPENDABLE
#define ABSTRACTIONS_WALLET_SPENDABLE

#include <abstractions/redeem/unspent.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <abstractions/pattern/pay_to_address.hpp>
#include <abstractions/pattern/pay_to_pubkey.hpp>

namespace abstractions::bitcoin {

    using redeemer = const abstractions::pattern::abstract::redeemer<secret, script,
        abstractions::transaction<input, output>>&;
    using payable = const abstractions::pattern::abstract::payable<secret, script>&;
    using pattern = const abstractions::pattern::abstract::pattern<secret, script,
        abstractions::transaction<input, output>>&;
    
    using unspent = redeem::unspent<script, txid, secret>;
    using spendable = redeem::spendable<script, txid, secret>;
    
    const auto pay_to_address_compressed =
        abstractions::pattern::pay_to_address<secret,
            bitcoin::pubkey, bitcoin::address,
            abstractions::transaction<input, output>>{};
    const auto pay_to_address_uncompressed =
        abstractions::pattern::pay_to_address<secret,
            bitcoin::uncompressed_pubkey, bitcoin::address, 
            abstractions::transaction<input, output>>{};
    const auto pay_to_pubkey_compressed =
        abstractions::pattern::pay_to_pubkey<secret,
            bitcoin::pubkey,
            abstractions::transaction<input, output>>{};
    const auto pay_to_pubkey_uncompressed = 
        abstractions::pattern::pay_to_pubkey<secret,
            bitcoin::uncompressed_pubkey,
            abstractions::transaction<input, output>>{};
    
}

#endif 
