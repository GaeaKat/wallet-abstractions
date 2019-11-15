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
    struct pay_to_pubkey final : public pattern::interface::recognizable<secret, pubkey, bytes, pubkey, tx> {
        using parent = pattern::interface::recognizable<secret, pubkey, bytes, pubkey, tx>;
        using parent::tag;
        using parent::pay;
                
        pubkey tag(const pubkey& k) const final override {
            return k;
        };
        
        bytes pay(const pubkey& k) const override {
            return script::compile(script::pay_to(k.Pubkey));
        }
        
        list<pubkey> recognize(bytes s) const override {
            return list<pubkey>::make(abstractions::script::pay_to_pubkey<pubkey>::to(s));
        }
        
        bytes redeem(output<bytes> o, input_index<tx> i, const secret& k) const override {
            return script::compile(script::redeem_from_pay_to_pubkey(
                secp256k1::sign(o.serialize(), bytes(i.Transaction), i.Index, k.Secret)));
        }
    
    };
    
}

#endif
