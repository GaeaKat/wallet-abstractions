// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_DEBIT
#define ABSTRACTIONS_REDEEM_DEBIT

#include <abstractions/abstractions.hpp>

namespace abstractions::redeem {
    
    template <typename out, typename point>
    struct debit {
        out Output;
        point Point;
        
        bool valid() const {
            return Output.valid() && Point.valid();
        }
        
        satoshi value() const {
            return Output.value();
        }
    };
}

#endif
