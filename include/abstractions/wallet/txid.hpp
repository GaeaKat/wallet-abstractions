#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/sha512.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using txid = ::data::sha512::digest;
        
        namespace hex {
            txid read(string& x);
            string write(txid& s);
        }
        
    }
    
} 

#endif
