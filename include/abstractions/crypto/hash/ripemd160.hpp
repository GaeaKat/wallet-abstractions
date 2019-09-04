// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_HASH_RIPEMD160
#define ABSTRACTIONS_CRYPTO_HASH_RIPEMD160

#include <data/crypto/ripemd160.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace ripemd160 {
        using digest = data::ripemd160::digest;
        
        inline digest hash(bytes& b) {
            return data::ripemd160::hash(b);
        }
        
        template <uint32 n>
        inline digest hash(const std::array<byte, n>& b) {
            return data::ripemd160::hash<n>(b);
        }

        template <uint32 n>
        inline digest hash(const data::uint<n>& b) {
            return data::ripemd160::hash<n>(b);
        }
    }

}

#endif

