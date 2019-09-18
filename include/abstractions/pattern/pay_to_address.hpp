// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/transaction.hpp>
#include <abstractions/script/pay_to_address.hpp>

namespace abstractions::pattern {
        
    template <typename secret, typename pubkey, typename address, typename tx>
    struct pay_to_address final : public pattern::abstract::pay_to_address<secret, pubkey, bytes, address, tx> {
        using script = bytes;
        using parent = pattern::abstract::pay_to_address<secret, pubkey, script, address, tx>;
        using parent::tag;
        using parent::pay;
        
        address tag(const pubkey& k) const final override {
            return k.address();
        }
        
        script pay(const address& a) const final override {
            return abstractions::script::pay_to(a)->compile();
        }
        
        list<address> recognize(script s) const final override {
            return list<address>{abstractions::script::pay_to_address::to(s)};
        }
        
        script redeem(satoshi amount, script script_pubkey, const tx& t, index i, const secret& k) const final override {
            abstractions::output<script> o{amount, script_pubkey};
            return abstractions::script::redeem_from_pay_to_address(
                secp256k1::sign(o, t, i, k.Secret), k.to_public().Pubkey)->compile();
        }
        
    };
    
}

#endif


