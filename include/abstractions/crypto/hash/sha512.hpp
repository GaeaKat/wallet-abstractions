// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_HASH_SHA512
#define ABSTRACTIONS_CRYPTO_HASH_SHA512

#include <data/crypto/sha512.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace sha512 {
        using digest = data::sha512::digest;
        
        inline digest hash(bytes& b) {
            return data::sha512::hash(b);
        }
        
        template <N n>
        inline digest hash(const std::array<byte, n>& b) {
            return data::sha512::hash<n>(b);
        }
        
        inline digest double_hash(bytes& b) {
            return data::sha512::hash<64>(static_cast<const std::array<byte, 64>&>(data::sha512::hash(b)));
        }
        
        template <N n>
        inline digest double_hash(const std::array<byte, n>& b) {
            return data::sha512::hash<64>(static_cast<const std::array<byte, 64>&>(data::sha512::hash<n>(b)));
        }
    }

}

#endif

