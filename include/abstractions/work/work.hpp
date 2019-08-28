// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WORK_WORK
#define ABSTRACTIONS_WORK_WORK

#include <abstractions/abstractions.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/wallet/keys.hpp>

namespace abstractions::work {
        
    using uint24 = uint32;
    
    struct target {
        uint32 Encoded;
        
        byte exponent() const {
            return byte(Encoded >> 24);
        }
        
        uint24 value() const {
            return Encoded & 0x00ffffff;
        }
        
        bool valid() const {
            return [](byte e, uint24 v)->bool{
                return e >= 3 && e <= 32 && v != 0;
            } (exponent(), value());
        }

    private:
        static uint32 encode(byte e, uint24 v) {
           if (e < 3 || e > 32 || v == 0 || v > 0x00ffffff) return 0;
           return (uint32(e) << 24) + v;
        }
        
    public:
        target() : Encoded{} {}
        target(uint32 x) : Encoded{x} {}
        target(byte e, uint24 v) : Encoded{encode(e, v)} {}
        
        sha256::digest expand() const {
            return data::math::number::bounded::uint<sha256::digest::size>{uint32(value())} << ((exponent() - 3) * 8);
        }
        
        operator uint32() const {
            return Encoded;
        }
        
        operator sha256::digest() const {
            return expand();
        }
        
        bool operator==(target t) const {
            return expand() == t.expand();
        } 
        
        bool operator!=(target t) const {
            return expand() != t.expand();
        } 
        
        bool operator<(target t) const {
            return expand() < t.expand();
        } 
        
        bool operator<=(target t) const {
            return expand() <= t.expand();
        } 
        
        bool operator>(target t) const {
            return expand() > t.expand();
        } 
        
        bool operator>=(target t) const {
            return expand() >= t.expand();
        } 
    };
    
    const target easy{32, 0xffffff}; 
    const target hard{3, 0x000001};
        
    const uint32 message_size = 36;
    using message = data::math::number::bounded::uint<9>;
    
    struct order {
        sha256::digest Reference;
        message Message;
        target Target;
        
        bool valid() const {
            return Reference.valid() && Target.valid();
        }
        
        order(sha256::digest r, message m, target t) : Reference{r}, Message{m}, Target{t} {}
        order() : Reference{}, Message{}, Target{} {}
    };
    
    struct candidate : data::uint<80> {
        uint32 version() const {
            return words()[0];
        }
        
        work::order order() const;
        
        work::target target() const {
            return words()[18];
        }
        
        uint32 nonce() const {
            return words()[19];
        }
        
        bool valid() const {
            return order().valid();
        };
        
        candidate(uint32 version, struct order o, uint32 nonce);
        candidate() : data::uint<80>{} {}
        
        bool satisfied() const {
            return sha256::hash<80>(static_cast<const data::uint<80>&>(*this)) < target().expand();
        }
    };
    
    inline message bitcoin_header(const sha256::digest& d, uint32 timestamp) {
        message m{};
        std::copy(d.Digest.begin(), d.Digest.end(), m.begin());
        m.words().set(8, timestamp);
        return m;
    };
    
    inline message public_key(const bitcoin::pubkey& d) {
        message m{};
        m.words().set(0, 0);
        std::copy(d.begin(), d.end(), m.begin() + 3);
        return m;
    };
    
    candidate work(order);
    
}

#endif

