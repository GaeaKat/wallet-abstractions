#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <data/crypto/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>
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
