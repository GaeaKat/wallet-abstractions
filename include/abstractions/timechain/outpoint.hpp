// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TIMECHAIN_OUTPOINT
#define ABSTRACTIONS_TIMECHAIN_OUTPOINT

#include <abstractions/abstractions.hpp>
#include "timechain.hpp"

namespace abstractions::timechain::outpoint {
    
    template <typename Outpoint, typename Digest, typename N>
    struct interface {
        
        // How much is stored in a given output?
        static Digest reference(Outpoint o) {
            return o.reference();
        }
        
        // What is the script defining how this output is redeemed. 
        static N index(Outpoint o) {
            return o.index();
        }
    
    };
    
    struct serialized {
        slice<byte, 36> Data;
        bool valid() const;
        digest reference() const;
        uint32 index() const;
        size_t size() const {
            return 36;
        }
        
        constexpr static interface<serialized, digest, uint32> is_outpoint{};
    };
    
    template <typename Outpoint>
    writer write(writer w, Outpoint o) {
        return w << digest(o.reference()) << uint32(o.index());
    }
    
    template <typename Outpoint>
    bytes serialize(Outpoint x) {
        bytes b{x.size(), 0};
        writer w{b};
        write(w, x);
        return b;
    }
    
} 

#endif
