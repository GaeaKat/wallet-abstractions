// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_SECP256K1
#define ABSTRACTIONS_CRYPTO_SECP256K1

#include <data/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include "address.hpp"

namespace abstractions::secp256k1 {
    
    using signature = data::crypto::secp256k1::signature;
    
    using secret = data::crypto::secp256k1::secret;
    
    using compressed_pubkey = data::crypto::secp256k1::compressed_pubkey;
    using uncompressed_pubkey = data::crypto::secp256k1::uncompressed_pubkey;
    
    signature sign(const bytes& output, const bytes& transaction, uint32 index, secret key);
    
    inline ripemd160::digest address(const compressed_pubkey& p) {
        sha256::digest digest=data::sha256::hash(p);
        return ripemd160::hash<sha256::size>(digest.Digest);
    }
    
    inline ripemd160::digest address(const uncompressed_pubkey& p) {
        return ripemd160::hash<data::crypto::secp256k1::uncompressed_pubkey_size>(p);
    }
    
    inline ripemd160::digest address_uncompressed(const secret& s) {
        return address(s.to_public_uncompressed());
    }
    
    inline ripemd160::digest address_compressed(const secret& s) {
        return address(s.to_public_compressed());
    }
    
    namespace wif {
        namespace compressed {
            // base58 with a checksum. Confusingly, the compressed format is longer
            // that the uncompressed format. That is because 'compressed' refers 
            // to whether the corresponding address is 
            bool read(string&, secret&);
            string write(const secret&);
            
            // hex.
            bool read(string&, compressed_pubkey&);
            string write(const compressed_pubkey&);
        }
        
        namespace uncompressed {
            // base58 with a checksum. 
            bool read(string&, secret&);
            string write(const secret&);
            
            // hex. 
            bool read(string&, uncompressed_pubkey&);
            string write(const uncompressed_pubkey&);
        }
    }
    
} 

#endif

