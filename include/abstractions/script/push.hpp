// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PUSH
#define ABSTRACTIONS_SCRIPT_PUSH

#include "script.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>

namespace abstractions::script {
    instruction push(bytes_view);
    instruction push(const bytes& b);
    instruction push(hex);
    instruction push(const secp256k1::uncompressed_pubkey&);
    instruction push(const secp256k1::compressed_pubkey&);
    instruction push(const ripemd160::digest&);
    instruction push(const sha256::digest&);
    instruction push(int64_little);
    instruction push(satoshi_little);
    instruction push(uint32_little);
    
    inline instruction push(bytes_view b) {
        return instruction{bytes{b.begin(), b.end()}};
    }
    
    inline instruction push(const bytes& b) {
        return instruction{b};
    }
    
    inline instruction push(hex h) {
        return instruction{(bytes)(h)};
    }
    
    inline instruction push(const sha256::digest& d) {
        return push(data::math::number::uint_little<sha256::digest::size>{d.Digest});
    }
    
    inline instruction push(const ripemd160::digest& d) {
        return push(data::math::number::uint_little<ripemd160::digest::size>{d.Digest});
    }
    
    inline instruction push(const secp256k1::uncompressed_pubkey& y) {
        return push(data::math::number::uint_little<secp256k1::uncompressed_pubkey_size>{y.Value});
    }
    
    inline instruction push(const secp256k1::compressed_pubkey& y) {
        return push(data::math::number::uint_little<secp256k1::compressed_pubkey_size>{y.Value});
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
