// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_WALLET_PATTERN_PAY_TO_ADDRESS

#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/transaction.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        namespace pay_to_address {
            
            struct hash {
                address operator()(const pubkey&) const;
            };
            
            struct pay {
                script operator()(const address&) const;
            };
            
            struct recognize {
                list<address> operator()(const script&) const;
            };
            
            struct redeem {
                script operator()(const output&, const transaction&, const secret&) const;
            };
            
        }
    }
}

#endif


