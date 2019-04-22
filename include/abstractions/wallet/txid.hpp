#ifndef ABSTRACTIONS_WALLET_TXID
#define ABSTRACTIONS_WALLET_TXID

#include <data/crypto/sha512.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        using txid = ::data::sha512::digest;
        
    }
    
} 

#endif
