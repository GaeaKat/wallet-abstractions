// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY
#define ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/transaction.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/pattern.hpp>
#include <abstractions/script/pay_to_pubkey.hpp>

namespace abstractions::pattern {
        
    template <typename secret, typename pubkey, typename tx>
    struct pay_to_pubkey final : public pattern::interface::pay_to_pubkey<secret, pubkey, bytes, tx> {
        using script = bytes;
        using parent = pattern::interface::pay_to_pubkey<secret, pubkey, script, tx>;
        using parent::tag;
        using parent::pay;
        
        script pay(const pubkey& k) const final override {
            return abstractions::script::pay_to(k.Pubkey)->compile();
        }
        
        list<pubkey> recognize(script s) const final override {
            return {abstractions::script::pay_to_pubkey<pubkey>::to(s)};
        }
        
        script redeem(output<bytes> o, input_index<tx> i, const secret& k) const final override {
            return abstractions::script::redeem_from_pay_to_pubkey(
                secp256k1::sign(abstractions::output<bytes>(o), i.Transaction, i.Index, k.Secret))->compile();
        }
    
    };
    
}

#endif
