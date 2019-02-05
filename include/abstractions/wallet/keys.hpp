#ifndef ABSTRACTIONS_WALLET_KEYS_HPP
#define ABSTRACTIONS_WALLET_KEYS_HPP

#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using pubkey = ::data::secp256k1::pubkey;
        
        using secret = ::data::secp256k1::pubkey;
    
        namespace wif {
            secret read(string& x);
            
            string write(secret& s);
        }
        
        namespace wif_compressed {
            secret read(string& x);
            
            string write(secret& s);
        }
        
        namespace hex {
            secret read(string& x);
            
            string write(secret& s);
            
            pubkey read(string& x);
            
            string write(pubkey& s);
        }
        
    }
    
} 

#endif

