#ifndef ABSTRACTIONS_SECP256K1
#define ABSTRACTIONS_SECP256K1

#include <data/crypto/secp256k1.hpp>

#include <abstractions/key.hpp>

namespace abstractions {
    
    namespace secp256k1 {

        using secret = data::secp256k1::secret;
        using to_public = key::to_public<data::secp256k1::pubkey, secret>;
            
        using pubkey = key::claim<data::secp256k1::pubkey, secret>;
        using pair = key::pair<data::secp256k1::pubkey, secret>;
    
    }
    
} 

#endif
