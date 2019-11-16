// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WORK_WORK
#define ABSTRACTIONS_WORK_WORK

#include <abstractions/abstractions.hpp>
#include <abstractions/crypto/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <data/encoding/halves.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::work {
    
    struct uint24 {
        uint32 Value;
        
        uint24(uint32 v) : Value{v & 0x00ffffff} {}
    };
    
    struct target {
        uint32 Encoded;
        
        byte exponent() const {
            return Encoded >> 24;
        }
        
        uint24 factor() const {
            return uint24{Encoded};
        }
        
        bool valid() const {
            return [](byte e, uint24 v)->bool{
                return e >= 3 && e <= 32 && v.Value != 0;
            } (exponent(), factor());
        }

    private:
        static uint32 encode(byte e, uint24 v) {
           if (e < 3 || e > 32 || v.Value == 0) return 0;
           return (uint32(e) << 24) + v.Value;
        }
        
    public:
        target() : Encoded{} {}
        target(uint32 x) : Encoded{x} {}
        target(byte e, uint24 v) : Encoded{encode(e, v)} {}
        
        sha256::digest expand() const {
            return data::uint<sha256::digest::size>{factor().Value} << ((exponent() - 3) * 8);
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
    
    const target success_half{32, 0x800000};
    const target success_quarter{32, 0x400000};
    const target success_eighth{32, 0x200000};
    const target success_sixteenth{32, 0x100000};
    
    const uint32 message_size = 68;
    using message = data::uint<68>;
    
    struct order {
        message Message;
        target Target;
        
        bool valid() const {
            return Target.valid();
        }
        
        order(message m, target t) : Message{m}, Target{t} {}
        order() : Message{}, Target{} {}
    };
    
    struct candidate {
        data::uint<80> Data;
        
        candidate() : Data{} {}
        candidate(data::uint<80> d) : Data{d} {}
        candidate(int64 i, order o);
        
        bool operator==(const candidate& c) {
            return Data == c.Data;
        }
        
        sha256::digest hash() const {
            return crypto::hash256(Data);
        }
        
        work::target target() const {
            throw data::method::unimplemented{"work::candidate::target"};
        }
    
        bool valid() const {
            return hash() < target().expand();
        }
        
        int64 nonce() const;
        
        work::message message() const;
    
        static data::uint<80> write(int64, order);
    };
    
    inline candidate::candidate(int64 i, order o) : Data{write(i, o)} {}
    
    message bitcoin_header(sha256::digest d, uint32 timestamp);
    
    message public_key(bitcoin::pubkey d);
    
    message reference_and_pubkey(sha256::digest, bitcoin::pubkey, uint24 sequence);
    
    inline message reference_and_pubkey(sha256::digest d, bitcoin::pubkey p) {
        return reference_and_pubkey(d, p, 0);
    }
    
    int64 work(order);
    
}

#endif

