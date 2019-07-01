// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_TRANSACTION
#define ABSTRACTIONS_WALLET_TRANSACTION

#include <abstractions/abstractions.hpp>
#include "input.hpp"
#include "output.hpp"
#include "txid.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct transaction : public abstractions::transaction<input, output> {
            using abstractions::transaction<input, output>::transaction;
            
            txid id() const;
            transaction(string hex);
            
            using representation = typename abstractions::transaction<input, output>::representation;
            
            transaction& operator=(transaction);
        };
        
    }
    
    namespace sha512 {
        inline bitcoin::txid hash(const bitcoin::transaction& b) {
            return data::sha512::hash(static_cast<bytes&>(b));
        }
    }
    
    namespace bitcoin {
            
        inline txid transaction::id() const {
            return sha512::hash(*this);
        }
        
    }

}

#endif
