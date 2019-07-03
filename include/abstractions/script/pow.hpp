// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_SCRIPT_POW
#define ABSTRACTIONS_SCRIPT_POW

#include "functions.hpp"
#include <abstractions/work/work.hpp>

namespace abstractions {
    
    namespace script {
        pointer<program> expand_target();
        pointer<program> lock_by_pow(work::message, work::target);
        
        inline pointer<program> lock_by_pow(work::message, work::target) {
            return sequence({
                dup(), 
                to_alt_stack(),
                concat(2),
                rotate_bits(-32),
                bitcoin_hash(),
                from_alt_stack(), 
                expand_target(), 
                greater()
            });
        }
    }
    
}

#endif

