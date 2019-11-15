// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/push.hpp>

namespace abstractions::script {
    
    instruction push(bitcoin::signature y) {
        bytes x{static_cast<unsigned char>(y.size())};
        std::copy(y.begin(), y.end(), x.begin());
        return push(x);
    }
    
    instruction push(bitcoin::pubkey y) {
        bytes x{static_cast<unsigned char>(y.Pubkey.size())};
        std::copy(y.Pubkey.begin(), y.Pubkey.end(), x.begin());
        return push(x);
    }
    
    instruction push(secp256k1::uncompressed_pubkey y) {
        bytes x{bitcoin::address::digest::size};
        std::copy(y.begin(), y.end(), x.begin());
        return push(x);
    }
    
    instruction push(secp256k1::compressed_pubkey y) {
        bytes x{bitcoin::address::digest::size};
        std::copy(y.begin(), y.end(), x.begin());
        return push(x);
    }
}

