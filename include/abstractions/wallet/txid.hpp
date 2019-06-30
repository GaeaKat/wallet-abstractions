// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_TXID
#define ABSTRACTIONS_WALLET_TXID

#include <data/crypto/sha512.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct txid : public pointer<::data::sha512::digest> {
            using pointer<::data::sha512::digest>::shared_ptr;
            txid(string hex);
            txid(::data::sha512::digest);
            txid(::data::sha512::digest&);
        };
        
    }
    
} 

#endif
