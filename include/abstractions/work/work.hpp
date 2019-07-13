// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WORK_WORK
#define ABSTRACTIONS_WORK_WORK

#include <abstractions/abstractions.hpp>
#include <abstractions/crypto/hash/sha256.hpp>

namespace abstractions {
    
    namespace work {
        
        using uint24 = std::array<byte, 3>;
        
        struct target {
            byte Exponent;
            uint24 Value;
            
            target(byte e, uint24 v);
            
            operator uint32_t();
        };
        
        const N message_size = 36;
        using message = std::array<byte, message_size>;
        
        struct candidate {
            sha256::digest Reference;
            message Message;
            target Target;
            
            bool valid() const;
            
            candidate(sha256::digest r, message m, target t) : Reference{r}, Message{m}, Target{t} {}
            candidate();
            
            bytes encode() const;
        };
        
        message reference(const sha256::digest d) {
            message m{};
            std::copy(d.begin(), d.end(), m.begin());
            return m;
        };
        
        uint32_t work(candidate);
    
    }
    
}

#endif

