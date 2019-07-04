// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_CRYPTO_HASH_RIPEMD160
#define ABSTRACTIONS_CRYPTO_HASH_RIPEMD160

#include <data/crypto/ripemd160.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace ripemd160 {
        using digest = data::ripemd160::digest;
        
        inline digest hash(const bytes& b) {
            return data::ripemd160::hash(b);
        }
        
        template <N n>
        inline digest hash(const std::array<byte, n>& b) {
            return data::ripemd160::hash(b);
        }
    }

}

#endif

