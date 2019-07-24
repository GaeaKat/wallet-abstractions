// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/pow.hpp>

namespace abstractions::script {
        
        pointer<program> push_pow_target(work::target);
        
        pointer<program> push_zero_bytes(uint32);
        
        pointer<program> expand_target() {
            return sequence({
                split(1), 
                to_alt(), 
                push_zero_bytes(29), 
                cat(), 
                from_alt(), 
                less_equal_32_verify(), 
                verify(), 
                op(program::OP_SPLIT), 
                cat()
            });
        }
        
        pointer<program> lock_by_pow(sha256::digest m, work::target t) {
            // The input that redeems this script will push a signature, a nonce, and a pubkey. 
            return sequence({
                to_alt(),            // move pubkey to alt stack
                push(m),
                push_zero_bytes(3),
                from_alt(),          // retrieve pubkey. 
                dup(),               // need two pubkeys. 
                to_alt(), 
                push_pow_target(t),
                dup(), 
                to_alt(),
                concat(5),
                rotate_bytes_left(4),
                bitcoin_hash(),
                from_alt(),          // retrieve target. 
                expand_target(), 
                less_256_verify(),
                check_signature()
            });
        }
}

