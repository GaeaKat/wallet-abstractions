// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_HASH
#define ABSTRACTIONS_WALLET_HASH

#include <abstractions/crypto/hash/sha256.hpp>

namespace abstractions {
    
    namespace bitcoin {
        inline sha256::digest hash(const bytes& b) {
            return sha256::double_hash(b);
        }
        
        template <N n>
        inline sha256::digest hash(const std::array<byte, n>& b) {
            return sha256::double_hash(b);
        }
    }

}

#endif
