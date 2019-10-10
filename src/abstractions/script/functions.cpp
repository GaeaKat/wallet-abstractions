// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/functions.hpp>

namespace abstractions::script {
    
    pointer<program> push(bitcoin::signature& y) {
        bytes x{static_cast<unsigned char>(y.size())};
        std::copy(y.begin(), y.end(), x.begin());
        return push_data(x);
    }
    
    pointer<program> push(bitcoin::pubkey& y) {
        bytes x{static_cast<unsigned char>(y.Pubkey.size())};
        std::copy(y.Pubkey.begin(), y.Pubkey.end(), x.begin());
        return push_data(x);
    }
    
    pointer<program> push(bitcoin::address& y) {
        bytes x{bitcoin::address::digest::size};
        std::copy(y.Digest.Digest.begin(), y.Digest.Digest.end(), x.begin());
        return push_data(x);
    }
}

