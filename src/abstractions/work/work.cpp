// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/work/work.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::work {
    
    // roughly 1/16 odds. 
    const target minimum{32, 0x000fffff};
    
    candidate::candidate(int64, order) {
        throw data::method::unimplemented{};
    }
    
    int64 work(order o) {
        if (o.Target < minimum) throw std::invalid_argument{"minimum target"};
        int64 nonce = 0;
        while (true) {
            if (candidate{nonce, o}.valid()) return nonce;
            nonce++;
        }
    }
    
}
