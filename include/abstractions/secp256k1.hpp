#ifndef ABSTRACTIONS_SECP256K1_HPP
#define ABSTRACTIONS_SECP256K1_HPP

#include "keypair.hpp"

namespace abstractions
{
    
    // incomplete implementation of secp256k1
    namespace secp256k1
    {

        // possible types that could be used with an implementation of bip32.
        const uint pubkey_size = 33;
        const uint secret_size = 32;

        const byte point_sign_even = 0x02;
        const byte point_sign_odd = 0x03;

        struct pubkey : public std::array<byte, pubkey_size> {
            bool valid() const;
            
            pubkey();
            pubkey(std::array<byte, pubkey_size> a) : std::array<byte, pubkey_size>(a) {}
        };
        
        struct secret : std::array<byte, secret_size> {
            bool valid() const;
            
            pubkey to_public() const;
            
            secret();
            secret(std::array<byte, secret_size> a) : std::array<byte, secret_size>(a) {}
        };
        
        using key = keypair<secret, pubkey>;

        bool valid(const pubkey&);

        bool valid(const secret&);
        
        inline bool pubkey::valid() const {
            return secp256k1::valid(*this);
        }
        
        inline bool secret::valid() const {
            return secp256k1::valid(*this);
        }

        const std::array<byte, pubkey_size - 1> max_public_key({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F});
    
    }
    
    template<> const secp256k1::pubkey zero<secp256k1::pubkey> = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    template<> const secp256k1::secret zero<secp256k1::secret> = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    inline secp256k1::pubkey::pubkey() : pubkey(zero<secp256k1::pubkey>) {}
    inline secp256k1::secret::secret() : secret(zero<secp256k1::secret>) {}

}

#endif
