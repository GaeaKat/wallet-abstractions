#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <data/crypto/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using address = ::data::sha256::digest;
        
        namespace bitcoin {
            address read(string& s);
            string write(address& a);
        }
        
        namespace cashaddr {
            address read(string& s);
            string write(address& a);
        }
    }
}

#endif
