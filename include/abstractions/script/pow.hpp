// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include <abstractions/work/work.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    inline pointer<program> lock_with_pow(sha256::digest, work::target) {
        throw data::method::unimplemented{};
    }
    
    struct pow_lock : public program {
        bytes Script;
        sha256::digest Reference; 
        work::target Target;
        
        static bool valid(const bytes& s) {
            throw data::method::unimplemented{};
        }
        
        bool valid() const {
            return valid(Script);
        }
        
        pow_lock(const bytes& s) {
            throw data::method::unimplemented{};
        }
        
        pow_lock() {}
        
        // TODO
        // virtual uint32 length() const final override;
    
        virtual void write(writer&) const final override {
            throw data::method::unimplemented{};
        }
        
    private :
        pow_lock(bytes s, sha256::digest r) : Script{s}, Reference{r} {} 
    };
    
    struct pow_key : public program {
        bytes Script;
        bitcoin::signature Signature;
        bitcoin::pubkey Pubkey;
        int64 Nonce;
        
        static bool valid(const bytes& s) {
            throw data::method::unimplemented{};
        }
        
        bool valid() const {
            return valid(Script);
        }
        
        pow_key(const bytes& s) {
            throw data::method::unimplemented{};
        }
        
        pow_key() {}
        
        // TODO
        //virtual uint32 length() const final override;
        
        virtual void write(writer&) const final override {
            throw data::method::unimplemented{};
        }
        
    private :
        pow_key(bytes b, 
        bitcoin::signature s,
        bitcoin::pubkey p,
        int64 n) : Script{b}, Signature{s}, Pubkey{p}, Nonce{n} {} 
    };
    
    inline work::candidate unlock(pow_lock& l, pow_key& k) {
        return work::candidate{k.Nonce, work::order{work::reference_and_pubkey(l.Reference, k.Pubkey), l.Target}};
    }
    
    inline pointer<program> unlock_with_pow(const bitcoin::signature& x, const bitcoin::pubkey& p, int64 nonce) {
        return sequence({push(x), push(p), push(nonce)});
    }
    
}

#endif

