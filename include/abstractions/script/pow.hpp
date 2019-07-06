// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include <abstractions/work/work.hpp>

namespace abstractions {
    
    namespace script {
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
        
        pointer<program> expand_target();
        pointer<program> lock_by_pow(work::message, work::target);
        
        pointer<program> push_pow_message(work::message);
        pointer<program> push_pow_target(work::target);
        
        pointer<program> push_target_zeros();
        
        inline pointer<program> expand_target() {
            return sequence({
                split(1), 
                swap(), 
                to_alt_stack(), 
                to_alt_stack(), 
                push_target_zeros(), 
                from_alt_stack(),
                concat(), 
                from_alt_stack(), 
                subtract(3), 
                rotate_bytes_right()
            });
        }
        
        inline pointer<program> lock_by_pow(work::message m, work::target t) {
            // The input that redeems this script will push a nonce, a signature, and a pubkey. 
            return sequence({
                to_alt_stack(), 
                dup(), 
                to_alt_stack(), 
                sha256_hash(), 
                push_pow_message(m),
                push_pow_target(t),
                dup(), 
                to_alt_stack(),
                concat(2),
                rotate_bytes(-4),
                bitcoin_hash(),
                from_alt_stack(), 
                expand_target(), 
                greater256(),
                from_alt_stack(), 
                from_alt_stack(), 
                check_signature()
            });
        }
    }
    
}

#endif

