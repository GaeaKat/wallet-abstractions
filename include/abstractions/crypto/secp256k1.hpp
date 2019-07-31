// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_SECP256K1
#define ABSTRACTIONS_WALLET_SECP256K1

#include <data/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>

namespace abstractions::secp256k1 {
    
    using signature = data::secp256k1::signature;
    
    using compressed_secret = data::secp256k1::compressed_secret;
    using compressed_pubkey = data::secp256k1::compressed_pubkey;
    
    using uncompressed_secret = data::secp256k1::uncompressed_secret;
    using uncompressed_pubkey = data::secp256k1::uncompressed_pubkey;
    
    inline ripemd160::digest address(const compressed_pubkey& p) {
        return ripemd160::hash<data::secp256k1::compressed_pubkey_size>(p);
    }
    
    inline ripemd160::digest address(const uncompressed_pubkey& p) {
        return ripemd160::hash<data::secp256k1::uncompressed_pubkey_size>(p);
    }
    
    inline ripemd160::digest address(const compressed_secret& s) {
        return address(s.to_public());
    }
    
    inline ripemd160::digest address(const uncompressed_secret& s) {
        return address(s.to_public());
    }
    
} 

#endif

