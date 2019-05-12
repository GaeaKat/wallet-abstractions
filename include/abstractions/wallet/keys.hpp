// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/abstractions.hpp>
#include "tag.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using pubkey = ::data::secp256k1::pubkey;
        
        using secret = ::data::secp256k1::secret;
    
        namespace wif {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
        namespace wif_compressed {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
    }
    
} 

#endif

