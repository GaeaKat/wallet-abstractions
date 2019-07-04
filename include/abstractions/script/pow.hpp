// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "math.hpp"
#include <abstractions/work/work.hpp>

namespace abstractions {
    
    namespace script {
        pointer<program> expand_target();
        pointer<program> lock_by_pow(work::message, work::target);
        
        pointer<program> push_pow_message(work::message);
        pointer<program> push_pow_target(work::target);
        
        pointer<program> push_target_zeros();
        
        pointer<program> expand_target() {
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
        
        inline pointer<program> lock_by_pow(work::candidate c) {
            return sequence({
                push_pow_message(c.Message),
                push_pow_target(c.Target),
                dup(), 
                to_alt_stack(),
                concat(2),
                rotate_bytes(-4),
                bitcoin_hash(),
                from_alt_stack(), 
                expand_target(), 
                greater256()
            });
        }
    }
    
}

#endif

