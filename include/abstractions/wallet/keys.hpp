// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <data/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
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
            
            explicit secret(string wif);
            
            bitcoin::address address() const;
        };
        
        struct pubkey : public data::secp256k1::pubkey, public tag {
            using parent = data::secp256k1::pubkey;
            using parent::pubkey;
            
            pubkey operator+(const pubkey&) const;
            pubkey operator*(const secret&) const;
            
            pubkey& operator=(const pubkey& p);
            
            explicit pubkey(string wif);
            
            bitcoin::address address() const;
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
        
        inline address address_hash(const pubkey& b) {
            return ripemd160::hash<data::secp256k1::pubkey_size>(
                static_cast<const std::array<byte, data::secp256k1::pubkey_size>&>(b));
        }
            
        inline pubkey secret::to_public() const {
            return secret::parent::to_public();
        }
            
        inline secret secret::operator+(const secret& s) const {
            return parent::operator+(static_cast<const parent&>(s));
        }
        
        inline secret secret::operator*(const secret& s) const {
            return parent::operator+(static_cast<const parent&>(s));
        }
            
        inline secret& secret::operator=(const secret& s) {
            parent::operator=(static_cast<const parent&>(s));
            return *this;
        }
            
        inline pubkey pubkey::operator+(const pubkey& p) const {
            return parent::operator+(static_cast<const parent&>(p));
        }
        
        inline pubkey pubkey::operator*(const secret& s) const {
            return parent::operator*(static_cast<const secret::parent&>(s));
        }
            
        inline pubkey& pubkey::operator=(const pubkey& p) {
            parent::operator=(static_cast<const parent&>(p));
            return *this;
        }
        
        inline bitcoin::address pubkey::address() const {
            return address_hash(*this);
        };
        
        inline bitcoin::address secret::address() const {
            return to_public().address();
        };
        
    }
    
} 

#endif

