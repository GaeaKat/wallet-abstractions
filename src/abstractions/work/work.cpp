// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/work/work.hpp>

namespace abstractions::work {
    
    work::order candidate::order() const {
        throw 0;
    }
    
    // roughly 1/16 odds. 
    const target minimum{32, 0x000fffff};
    
    candidate work(order o) {
        if (o.Target < minimum) return {};
        uint64 nonce = 0;
        while (true) {
            candidate c{data::lesser(nonce), o, data::greater(nonce)};
            if (c.satisfied()) return c;
            nonce++;
        }
    }
    
}
