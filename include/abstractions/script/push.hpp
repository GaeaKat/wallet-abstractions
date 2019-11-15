// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PUSH
#define ABSTRACTIONS_SCRIPT_PUSH

#include "script.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>

namespace abstractions::script {
    instruction push(hex);
    instruction push(bitcoin::signature);
    instruction push(bitcoin::pubkey);
    instruction push(secp256k1::uncompressed_pubkey);
    instruction push(secp256k1::compressed_pubkey);
    instruction push(bitcoin::address);
    instruction push(sha256::digest);
    instruction push(int64_little);
    instruction push(satoshi_little);
    instruction push(uint32_little);
    
    inline instruction push(hex h) {
        return instruction{(bytes)(h)};
    }
    
    inline instruction push(bitcoin::address y) {
        return push(y.Digest);
    }
    
    inline instruction push(sha256::digest) {
        throw data::method::unimplemented{"abstractions::script::push(sha256::digest)"};
    }
    
    inline instruction push(int64_little) {
        throw data::method::unimplemented{"abstractions::script::push(int64_little)"};
    }
    
    inline instruction push(satoshi_little) {
        throw data::method::unimplemented{"abstractions::script::push(satoshi_little)"};
    }
    
    inline instruction push(uint32_little) {
        throw data::method::unimplemented{"abstractions::script::push(uint32_little)"};
    }
}

#endif
