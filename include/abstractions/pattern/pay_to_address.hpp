// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/transaction.hpp>
#include <abstractions/script/pay_to_address.hpp>

namespace abstractions::pattern {
        
    template <typename secret, typename pubkey, typename address, typename tx>
    struct pay_to_address final : public pattern::interface::recognizable<secret, pubkey, bytes, address, tx> {
        using script = bytes;
        using parent = pattern::interface::recognizable<secret, pubkey, script, address, tx>;
        using parent::tag;
        using parent::pay;
        
        address tag(const pubkey& k) const override {
            return k.address();
        }
        
        script pay(const address& a) const override {
            return abstractions::script::pay_to(a)->compile();
        }
        
        list<address> recognize(script s) const override {
            return list<address>::make(abstractions::script::pay_to_address::to(s));
        }
        
        script redeem(output<bytes> o, input_index<tx> i, const secret& k) const override {
            return abstractions::script::redeem_from_pay_to_address(
                secp256k1::sign(o.serialize(), bytes(i.Transaction), i.Index, k.Secret), k.to_public().Pubkey)->compile();
        }
        
    };
    
}

#endif


