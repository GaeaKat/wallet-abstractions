// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/pattern.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct pay_to_address final : public pattern::abstract::standard<secret, pubkey, script, address, transaction, machine> {
            
            address tag(pubkey k) const final override {
                return hash(k);
            }
            
            script pay(address a) const final override;
            
            list<address> recognize(script s) const final override;
            
            script redeem(satoshi amount, script script_pubkey, transaction t, secret k) const final override;
        
        };
            
    }
}

#endif


