// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WORK_WORK
#define ABSTRACTIONS_WORK_WORK

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace work {
        
        using uint24 = std::array<byte, 3>;
        
        struct target {
            byte Exponent;
            uint24 Value;
            
            target(byte e, uint24 v);
            
            operator uint32_t();
        };
        
        using message = std::array<byte, 68>;
        
        struct candidate {
            message Message;
            target Target;
            
            candidate(message m, target t) : Message{m}, Target{t} {}
        };
    
    }
    
}

#endif

