// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include <abstractions/work/work.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions::script {
    pointer<program> lock_by_pow(sha256::digest, work::target);
    pointer<program> unlock_with_pow(bitcoin::signature&, uint64 nonce, bitcoin::pubkey&);
    
    struct pow_lock : public program {
        bytes Script;
        work::candidate Candidate; 
        
        static bool valid(bytes& s);
        bool valid() const {
            return valid(Script);
        }
        
        pow_lock(bytes& s);
        pow_lock() {}
        
    private :
        pow_lock(bytes s, work::candidate c) : Script{s}, Candidate{c} {} 
    };
    
    inline pointer<program> unlock_with_pow(bitcoin::signature& x, uint64 nonce, bitcoin::pubkey& p) {
        return sequence({push(x), push(nonce), push(p)});
    }
    
}

#endif

