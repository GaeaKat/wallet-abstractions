#ifndef ABSTRACTIONS_WALLET_HPP
#define ABSTRACTIONS_WALLET_HPP

#include <abstractions/blockchain/output.hpp>
#include <tuple>
#include "data.hpp"

namespace abstractions
{
    
    template <typename point, typename out>
    using wallet = map<point, out>;
    
    template <typename point, typename out>
    N balance(output::value<out> v, wallet<point, out> w) {
        int b = 0;
        for (std::tuple<point, out> pointout : w) b += v(std::get<1>(pointout)); 
        return b;
    }
    
}

#endif
