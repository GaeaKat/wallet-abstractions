// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_HASH
#define ABSTRACTIONS_WALLET_HASH

#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/sha512.hpp>

namespace abstractions {
    
    namespace bitcoin {
        inline sha256::digest hash256(const bytes& b) {
            return sha256::double_hash(b);
        }
        
        template <N n>
        inline sha256::digest hash256(const std::array<byte, n>& b) {
            return sha256::double_hash(b);
        }
        
        inline sha512::digest hash512(const bytes& b) {
            return sha512::double_hash(b);
        }
        
        template <N n>
        inline sha512::digest hash512(const std::array<byte, n>& b) {
            return sha512::double_hash(b);
        }
    }

}

#endif
