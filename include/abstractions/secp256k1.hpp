#ifndef ABSTRACTIONS_SECP256K1_HPP
#define ABSTRACTIONS_SECP256K1_HPP

#include "fundamental.hpp"
#include "abstractions.hpp"

namespace abstractions {
    
    // incomplete implementation of secp256k1
    namespace secp256k1
    {

        // possible types that could be used with an implementation of bip32.
        const uint pubkey_size = 33;
        const uint secret_size = 32;

        const byte point_sign_even = 0x02;
        const byte point_sign_odd = 0x03;
    
        const std::array<byte, pubkey_size> zero_pubkey{};
        const std::array<byte, secret_size> zero_secret{};

        const std::array<byte, pubkey_size - 1> max_public_key{{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F}};
        
        struct pubkey;
        
        struct secret : std::array<byte, secret_size> {
            
            bool valid() const;
            
            byte& operator[](N n) const {
                return static_cast<std::array<byte, secret_size>>(*this)[n];
            }
            
            pubkey to_public() const;
            
            secret() : std::array<byte, secret_size>{zero_secret} {}
            secret(std::array<byte, secret_size> a) : std::array<byte, secret_size>(a) {}
        };

        struct pubkey : public std::array<byte, pubkey_size> {
            bool valid() const;
            
            byte& operator[](N n) const {
                return static_cast<std::array<byte, pubkey_size>>(*this)[n];
            }
            
            pubkey operator+(const pubkey) const;
            pubkey operator*(const secret) const;
            
            pubkey() : std::array<byte, pubkey_size>{zero_pubkey} {}
            pubkey(std::array<byte, pubkey_size> a) : std::array<byte, pubkey_size>(a) {}
            
            static pubkey identity() {
                return pubkey{};
            }
        };
        
        const pubkey to_public(const secret&);
    
    }

}

#endif
