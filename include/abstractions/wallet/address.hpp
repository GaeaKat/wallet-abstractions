// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <data/crypto/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/abstractions.hpp>
#include "tag.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct address : public ::data::sha256::digest, public tag {};
        
        namespace bitcoin_address {
            bool read(stringstream&, address&);
            string write(address&);
            void write(address&, stringstream&);
        }
        
        namespace cashaddr {
            bool read(stringstream&, address&);
            string write(address&);
            void write(address&, stringstream&);
        }
    }
}

#endif
