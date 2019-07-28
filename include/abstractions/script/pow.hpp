// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include <abstractions/work/work.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/wallet/keys.hpp>

namespace abstractions::script {
    pointer<program> lock_by_pow(sha256::digest, work::target);
    pointer<program> unlock_with_pow(bitcoin::signature&, bitcoin::pubkey&, uint64 nonce);
    
    struct pow_lock : public program {
        bytes Script;
        work::order Order; 
        
        static bool valid(bytes& s);
        bool valid() const {
            return valid(Script);
        }
        
        pow_lock(bytes& s);
        pow_lock() {}
        
    private :
        pow_lock(bytes s, work::order o) : Script{s}, Order{o} {} 
    };
    
    struct pow_key : public program {
        bytes Script;
        bitcoin::signature Signature;
        bitcoin::pubkey Pubkey;
        uint64 Nonce;
        
        static bool valid(bytes& s);
        bool valid() const {
            return valid(Script);
        }
        
        pow_key(bytes& s);
        pow_key() {}
        
    private :
        pow_key(bytes b, 
        bitcoin::signature s,
        bitcoin::pubkey p,
        uint64 n) : Script{b}, Signature{s}, Pubkey{p}, Nonce{n} {} 
    };
    
    work::candidate unlock(pow_lock& l, pow_key& k);
    
    inline pointer<program> unlock_with_pow(bitcoin::signature& x, bitcoin::pubkey& p, uint64 nonce) {
        return sequence({push(x), push(p), push(nonce)});
    }
    
}

#endif

