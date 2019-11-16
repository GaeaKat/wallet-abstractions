// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/push.hpp>

namespace abstractions::script {
    
    instruction push(bytes_view b) {
        return instruction{bytes{b.begin(), b.end()}};
    }
    
    instruction push(const secp256k1::uncompressed_pubkey& y) {
        return instruction{bytes{y.begin(), y.end()}};
    }
    
    instruction push(const secp256k1::compressed_pubkey& y) {
        return instruction{bytes{y.begin(), y.end()}};
    }
}

