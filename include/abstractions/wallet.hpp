#ifndef ABSTRACTIONS_WALLET_HPP
#define ABSTRACTIONS_WALLET_HPP

#include <abstractions/blockchain/output.hpp>
#include "data.hpp"

namespace abstractions
{
    
    template <typename out>
    using wallet = set<out>;
    
    template <typename out>
    N balance(output::value<out> v, wallet<out> w) {
        if (w == nullptr) return 0;
        return v(w->First) + balance(v, w->Rest);
    }
    
}

#endif
