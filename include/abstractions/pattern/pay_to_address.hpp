// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS
#define ABSTRACTIONS_PATTERN_PAY_TO_ADDRESS

#include <data/crypto/secp256k1.hpp>
#include <data/crypto/sha256.hpp>
#include <abstractions/transaction.hpp>
#include <abstractions/pattern.hpp>

namespace abstractions {
    
    namespace script {
        using digest = data::sha256::digest;
        using pubkey = data::secp256k1::pubkey;
        using secret = data::secp256k1::secret;
            
        struct hash {
            digest operator()(const pubkey&) const;
        };
            
        struct pay {
            bytes operator()(const digest&) const;
        };
            
        struct recognize {
            list<digest> operator()(const bytes) const;
        };
            
        struct redeem {
            bytes operator()(const output<bytes>&, const bytes&, const secret&) const;
        };
        
        template <typename machine> 
        using pay_to_address = abstractions::pattern::pay_to_address<secret, pubkey, bytes, digest, pay, redeem, recognize, hash, bytes, machine>;
            
    }
}

#endif


