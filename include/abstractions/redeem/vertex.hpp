// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_VERTEX
#define ABSTRACTIONS_REDEEM_VERTEX

#include <abstractions/abstractions.hpp>
#include <abstractions/value.hpp>

namespace abstractions::redeem {
    
    template <typename in, typename out>
    struct vertex {
        queue<in> Inputs;
        queue<out> Outputs;
        
        vertex() : Inputs{}, Outputs{} {}
        vertex(queue<in> i, queue<out> o) : Inputs{i}, Outputs{o} {}
        
        bool valid() const;
        
        satoshi redeemed() const {
            return reduce([](in a, in b)->satoshi{
                return value(a) + value(b);
            }, Inputs);
        }
        
        satoshi spent() const {
            return reduce([](out a, out b)->satoshi{
                return value(a) + value(b);
            }, Inputs);
        }
        
        satoshi fee() const {
            return [](satoshi r, satoshi s)->satoshi{if (s > r) return 0; return r - s;}(redeemed(), spent());
        }
    };
    
} 

#endif
