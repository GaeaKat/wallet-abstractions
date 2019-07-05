// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/pattern.hpp>
#include <abstractions/script/pay_to_address.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct pay_to_address final : public pattern::abstract::standard<secret, pubkey, script, address, transaction, machine> {
            
            address tag(pubkey k) const final override {
                return hash(k);
            }
            
            script pay(address a) const final override {
                return abstractions::script::pay_to(a)->compile();
            }
            
            list<address> recognize(script s) const final override {
                return {abstractions::script::pay_to_address::to(s)};
            }
            
            script redeem(satoshi amount, script script_pubkey, transaction t, N index, secret k) const final override {
                return abstractions::script::redeem_from_pay_to_address(bitcoin::sign(bitcoin::output{amount, script_pubkey}, t, index, k), k.to_public())->compile();
            }
        
        };
            
    }
}

#endif


