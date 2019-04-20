#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using pubkey = ::data::secp256k1::pubkey;
        
        using secret = ::data::secp256k1::secret;
    
        namespace wif {
            secret read(string& x);
            string write(secret& s);
        }
        
        namespace wif_compressed {
            secret read(string& x);
            string write(secret& s);
        }
        
        namespace hex {            
            pubkey read(string& x);
            string write(pubkey& s);
        }
        
    }
    
} 

#endif

