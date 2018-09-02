#ifndef ABSTRACTIONS_WALLET_HPP
#define ABSTRACTIONS_WALLET_HPP

#include "output.hpp"
#include "list.hpp"
#include "link.hpp"

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
