// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_KEYS
#define ABSTRACTIONS_WALLET_KEYS

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/crypto/hash/ripemd160.hpp>
#include <data/crypto/one_way.hpp>
#include "tag.hpp"
#include "address.hpp"

namespace abstractions::bitcoin {
    
    struct pubkey;
    struct uncompressed_pubkey;
    
    using signature = secp256k1::signature;
    
    struct secret {
        secp256k1::secret Secret;
        secret() : Secret{} {}
        secret(const secp256k1::secret& s) : Secret{s} {}
        
        bool valid() const {
            return Secret.valid();
        }
        
        pubkey to_public() const;
        uncompressed_pubkey to_public_uncompressed() const;
        
        secret operator+(const secret&) const;
        secret operator*(const secret&) const;
        bool operator==(const secret&) const;

        
        explicit secret(string wif);
        
        bitcoin::address address() const;
        bitcoin::address address_uncompressed() const;
        inline string write();
        string write_uncompressed();
    };
    
    struct pubkey : public tag {
        secp256k1::compressed_pubkey Pubkey;
        pubkey() : Pubkey{} {}
        pubkey(const secp256k1::compressed_pubkey p) : Pubkey{p} {}
        
        bool valid() const {
            return Pubkey.valid();
        }
        
        pubkey operator+(const pubkey&) const;
        pubkey operator*(const secret&) const;
        bool operator==(const pubkey&) const;


        explicit pubkey(string hex);
        
        bitcoin::address address() const;
        string write();
    };
    
    struct uncompressed_pubkey : public tag {
        secp256k1::uncompressed_pubkey Pubkey;
        uncompressed_pubkey() : Pubkey{} {}
        uncompressed_pubkey(const secp256k1::uncompressed_pubkey p) : Pubkey{p} {}
        
        bool valid() const {
            return Pubkey.valid();
        }
        
        uncompressed_pubkey operator+(const uncompressed_pubkey&) const;
        uncompressed_pubkey operator*(const secret&) const;
        explicit uncompressed_pubkey(string hex);
        
        bitcoin::address address() const;
        string write();
    };
    
    constexpr data::math::module<pubkey, secret> is_module{};
    constexpr data::crypto::signature_scheme<secret, pubkey, const sha256::digest, signature> is_signature_scheme{};
    
}

namespace data::crypto {
    template <> struct to_public<
        abstractions::bitcoin::secret, 
        abstractions::bitcoin::uncompressed_pubkey>
            : function::abstract<abstractions::bitcoin::uncompressed_pubkey, const abstractions::bitcoin::secret&> {
        abstractions::bitcoin::uncompressed_pubkey operator()(
            const abstractions::bitcoin::secret& s) const noexcept final override {
            return s.to_public_uncompressed();
        }
    };
    
    template <> struct to_public<
        abstractions::bitcoin::secret, 
        abstractions::bitcoin::pubkey>
            : function::abstract<abstractions::bitcoin::pubkey, const abstractions::bitcoin::secret&> {
        abstractions::bitcoin::pubkey operator()(
            const abstractions::bitcoin::secret& s) const noexcept final override {
            return s.to_public();
        }
    };
}

namespace abstractions::bitcoin {
    inline pubkey secret::to_public() const {
        return Secret.to_public_compressed();
    }
    
    inline uncompressed_pubkey secret::to_public_uncompressed() const {
        return Secret.to_public_uncompressed();
    }
    
    inline secret secret::operator+(const secret& s) const {
        return Secret + s.Secret;
    }
    
    inline secret secret::operator*(const secret& s) const {
        return Secret * s.Secret;
    }

    inline bool secret::operator==(const secret &s) const {
        return Secret == s.Secret;
    }
    
    inline pubkey pubkey::operator+(const pubkey& p) const {
        return Pubkey + p.Pubkey;
    }
    
    inline pubkey pubkey::operator*(const secret& s) const {
        return Pubkey * s.Secret;
    }
    inline bool pubkey::operator==(const pubkey &p) const {
        return Pubkey == p.Pubkey;
    }

    inline uncompressed_pubkey uncompressed_pubkey::operator+(const uncompressed_pubkey& p) const {
        return Pubkey + p.Pubkey;
    }
    
    inline uncompressed_pubkey uncompressed_pubkey::operator*(const secret& s) const {
        return Pubkey * s.Secret;
    }
    
    inline bitcoin::address pubkey::address() const {
        return secp256k1::address(Pubkey);
    }
    
    inline bitcoin::address uncompressed_pubkey::address() const {
        return secp256k1::address(Pubkey);
    }
    
    inline bitcoin::address secret::address() const {
        return secp256k1::address_compressed(Secret);
    }
    
    inline bitcoin::address secret::address_uncompressed() const {
        return secp256k1::address_compressed(Secret);
    }
    
    inline string secret::write() {
        return secp256k1::wif::compressed::write(Secret);
    }
    
    inline string secret::write_uncompressed() {
        return secp256k1::wif::uncompressed::write(Secret);
    }

    inline secret::secret(string wif) : Secret{} {
        if (!secp256k1::wif::compressed::read(wif, Secret)) 
            secp256k1::wif::uncompressed::read(wif, Secret);
    }

    inline pubkey::pubkey(string hex) : Pubkey{} {
        secp256k1::wif::compressed::read(hex, Pubkey);
    }

    inline string pubkey::write() {
        return secp256k1::wif::compressed::write(Pubkey);
    }


    inline uncompressed_pubkey::uncompressed_pubkey(string hex) : Pubkey{} {
        secp256k1::wif::uncompressed::read(hex, Pubkey);
    }
    
} 

#endif

