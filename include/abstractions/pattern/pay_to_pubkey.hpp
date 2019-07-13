// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY
#define ABSTRACTIONS_PATTERN_PAY_TO_PUBKEY

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/pattern.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct pay_to_pubkey final : public pattern::abstract::standard<secret, pubkey, script, pubkey, transaction, machine> {
            
            pubkey tag(pubkey k) const final override {
                return k;
            };
            
            script pay(pubkey k) const final override;
            
            list<pubkey> recognize(script s) const final override;
            
            script redeem(satoshi amount, script s, transaction t, secret k) const final override;
        
        };
            
    }
}

#endif
