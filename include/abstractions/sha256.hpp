#ifndef ABSTRACTIONS_SHA256_HPP
#define ABSTRACTIONS_SHA256_HPP

#include "abstractions.hpp"

namespace abstractions
{
    
    namespace sha256
    {

        // possible types that could be used with an implementation of bip32.
        const uint size = 32;

        struct digest : public std::array<byte, size> {
            bool valid() const;
            
            byte operator[](N n) const {
                return static_cast<std::array<byte, sha256::size>>(*this)[n];
            }
            
            digest();
            digest(std::array<byte, sha256::size> a) : std::array<byte, sha256::size>(a) {}
        };
        
        const digest zero = digest{};
        
        inline bool digest::valid() const {
            return *this == zero;
        }
        
        inline digest::digest() : std::array<byte, sha256::size>() {}
    
    }

}

#endif

