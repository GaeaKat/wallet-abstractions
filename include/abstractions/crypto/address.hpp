// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_ADDRESS
#define ABSTRACTIONS_CRYPTO_ADDRESS

#include <data/crypto/one_way.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/sha512.hpp>

namespace abstractions::crypto {
    
    // template specialize this if you have your
    // own definition of the sign for your types. 
    template <typename addr, typename pk> 
    struct address : data::function::abstract<addr, pk> {
        address() = delete;
        
        addr operator()(pk s) const final override;
    };
    
    template <typename sk, typename pk, typename addr> 
    struct address_scheme : public data::crypto::keypair<sk, pk> {
        addr address(const pk s) const;
    };
    
    inline sha256::digest hash256(const bytes& b) {
        return sha256::double_hash(b);
    }
    
    template <uint32 n>
    inline sha256::digest hash256(const std::array<byte, n>& b) {
        return sha256::double_hash(b);
    }
    
    inline sha512::digest hash512(const bytes& b) {
        return sha512::double_hash(b);
    }
    
    template <uint32 n>
    inline sha512::digest hash512(const std::array<byte, n>& b) {
        return sha512::double_hash(b);
    }
    
    std::array<byte, 4> checksum(const slice<byte>&);
    
    bool verify_checksum(const slice<byte>&);
    
    inline sha256::digest txid(bytes& tx) {
        return hash256(tx);
    }
    
} 

#endif
