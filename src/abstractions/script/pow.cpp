// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/pow.hpp>

namespace abstractions::script {
    
    instruction push_pow_target(work::target) {
        throw data::method::unimplemented{"script::push_pow_target"};
    }
    
    instruction push_zero_bytes(uint32) {
        throw data::method::unimplemented{"script::push_zero_bites"};
    }
    
    program expand_target() {
        return program{} + split(1) + to_alt() + push_zero_bytes(29) +  
            cat() + from_alt() + less_equal_verify() + 
            verify() + op_code(OP_SPLIT) + cat();
    }
    
    program lock_by_pow(sha256::digest m, work::target t) {
        // The input that redeems this script will push a signature, a nonce, and a pubkey. 
        return program{} + 
            swap() +               // swap nonce and pubkey. 
            to_alt() +             // move pubkey to alt stack
            push(m) + 
            push_zero_bytes(3) + 
            from_alt() +           // retrieve pubkey. 
            dup() +                // need two pubkeys. 
            to_alt() + 
            push_pow_target(t) + 
            dup() + 
            to_alt() + 
            concat(5) + 
            rotate_bytes_left(4) + 
            bitcoin_hash() + 
            from_alt() +           // retrieve target. 
            expand_target() + 
            less_256_verify() + 
            check_signature();
    }
}
