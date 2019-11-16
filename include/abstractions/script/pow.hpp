// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include "push.hpp"
#include <abstractions/work/work.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    inline program lock_with_pow(sha256::digest, work::target) {
        throw data::method::unimplemented{"script::lock_with_pow"};
    }
    
    struct pow_lock {
        sha256::digest Reference; 
        work::target Target;
        
        static bool valid(const bytes& s) {
            throw data::method::unimplemented{"script::pow_lock::valid"};
        }
        
        bool valid() const {
            return Reference.valid() && Target.valid();
        }
        
        pow_lock(const bytes& s) {
            throw data::method::unimplemented{"script::pow_lock{}"};
        }
        
        pow_lock() {}
    };
    
    struct pow_key : public program {
        bitcoin::signature Signature;
        bitcoin::pubkey Pubkey;
        int64 Nonce;
        
        static bool valid(const bytes& s) {
            throw data::method::unimplemented{"script::pow_lock::valid"};
        }
        
        bool valid() const {
            return Pubkey.valid();
        }
        
        pow_key(const bytes& s) {
            throw data::method::unimplemented{"script::pow_key{}"};
        }
        
        pow_key() {}
        
    private :
        pow_key(
        bitcoin::signature s,
        bitcoin::pubkey p,
        int64 n) : Signature{s}, Pubkey{p}, Nonce{n} {} 
    };
    
    inline work::candidate unlock(pow_lock& l, pow_key& k) {
        return work::candidate{k.Nonce, work::order{work::reference_and_pubkey(l.Reference, k.Pubkey), l.Target}};
    }
    
    inline program unlock_with_pow(const bitcoin::signature& x, const bitcoin::pubkey& p, int64 nonce) {
        return program{} + push(x) + push(p.Pubkey) + push(int64_little{nonce});
    }
    
}

#endif

