// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_HASH_SHA256
#define ABSTRACTIONS_CRYPTO_HASH_SHA256

#include <data/crypto/sha256.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace sha256 {
        using namespace data::sha256;
        
        inline digest double_hash(const bytes& b) {
            return data::sha256::hash<32>(data::sha256::hash(b).Digest);
        }
        
        template <uint32 n>
        inline digest double_hash(const std::array<byte, n>& b) {
            return data::sha256::hash<32>(data::sha256::hash<n>(b).Digest);
        }
    }

}

#endif

