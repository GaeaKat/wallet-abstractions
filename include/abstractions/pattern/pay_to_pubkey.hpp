// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY
#define ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/pattern.hpp>
#include <abstractions/script/pay_to_pubkey.hpp>

namespace abstractions::pattern {
        
    template <typename secret, typename pubkey, typename tx>
    struct pay_to_pubkey final : public pattern::abstract::standard<secret, pubkey, bytes, pubkey, tx> {
        using script = bytes;
        
        pubkey tag(pubkey k) const final override {
            return k;
        }
        
        script pay(pubkey k) const final override {
            return abstractions::script::pay_to(k)->compile();
        }
        
        list<pubkey> recognize(script s) const final override {
            return {abstractions::script::pay_to_pubkey<pubkey>::to(s)};
        }
        
        script redeem(satoshi amount, script s, tx t, index i, secret k) const final override {
            return abstractions::script::redeem_from_pay_to_pubkey(
                bitcoin::sign(bitcoin::output{amount, s}, t, i, k))->compile();
        }
    
    };
    
}

#endif
