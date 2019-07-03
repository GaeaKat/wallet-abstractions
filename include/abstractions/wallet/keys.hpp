// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/sha256.hpp>
#include "tag.hpp"
#include "hash.hpp"
#include "address.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey;
        
        using signature = data::secp256k1::signature;
        
        struct secret : public data::secp256k1::secret {
            using parent = data::secp256k1::secret;
            using parent::secret;
            
            pubkey to_public() const;
            
            secret operator+(const secret&) const;
            secret operator*(const secret&) const;
            
            secret& operator=(const secret& s);
            
            signature sign(const sha256::digest&) const;
            
            secret(string wif);
        };
        
        struct pubkey : public data::secp256k1::pubkey, public tag {
            using parent = data::secp256k1::pubkey;
            using parent::pubkey;
            
            pubkey operator+(const pubkey&) const;
            pubkey operator*(const secret&) const;
            
            pubkey& operator=(const pubkey& p);
            
            bool verify(const sha256::digest&, const signature&) const;
            
            pubkey(string wif);
        };
        
        constexpr data::math::module<pubkey, secret> is_module{};
        constexpr data::crypto::signature_scheme<secret, pubkey, const sha256::digest, signature> is_signature_scheme{};
    
        namespace wif {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
        namespace wif_compressed {
            bool read(string&, secret&);
            string write(secret&);
            void write(secret&, stringstream&);
        }
        
        inline address hash(pubkey& b) {
            return bitcoin::hash<data::secp256k1::pubkey_size>(static_cast<std::array<byte, data::secp256k1::pubkey_size>&>(b));
        }
        
    }
    
} 

#endif

