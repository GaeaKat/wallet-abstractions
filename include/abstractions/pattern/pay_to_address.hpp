// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/pattern.hpp>
#include <abstractions/script/pay_to_address.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct pay_to_address final : public pattern::abstract::standard<secret, pubkey, script, address, transaction> {
            
            address tag(pubkey k) const final override {
                return k.address();
            }
            
            script pay(address a) const final override {
                return abstractions::script::pay_to(a)->compile();
            }
            
            list<address> recognize(script s) const final override {
                return {abstractions::script::pay_to_address::to(s)};
            }
            
            script redeem(satoshi amount, script script_pubkey, transaction t, index i, secret k) const final override {
                return abstractions::script::redeem_from_pay_to_address(bitcoin::sign(bitcoin::output{amount, script_pubkey}, t, i, k), k.to_public())->compile();
            }
        
        };
            
    }
}

#endif


