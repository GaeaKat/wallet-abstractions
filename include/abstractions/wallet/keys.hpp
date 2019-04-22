#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>
#include "tag.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey : public ::data::secp256k1::pubkey, public tag {};
        
        struct secret : public ::data::secp256k1::secret {};
    
        namespace wif {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret& s, stringstream& s);
        }
        
        namespace wif_compressed {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
    }
    
} 

#endif

