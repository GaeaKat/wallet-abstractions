// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_ADDRESS
#define ABSTRACTIONS_CRYPTO_ADDRESS

#include <data/crypto/one_way.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
//#include <abstractions/crypto/hash/sha512.hpp>

namespace abstractions::crypto {
    
    template <typename sk, typename pk, typename addr> 
    struct address_scheme : public data::crypto::keypair<sk, pk> {
        addr address(const pk s) const;
    };
    
    template <typename A>
    inline sha256::digest hash256(A a) {
        return sha256::double_hash(a);
    }
    
    /*template <typename A>
    inline sha512::digest hash512(A a) {
        return sha512::double_hash(a);
    }*/
    
    template <typename A>
    inline ripemd160::digest hash160(A a) {
        return ripemd160::hash(sha256::hash(a));
    }
    
    std::array<byte, 4> checksum(bytes_view);
    
    bool verify_checksum(bytes_view);
    
    inline sha256::digest txid(bytes_view tx) {
        return hash256(tx);
    }
    
} 

#endif
