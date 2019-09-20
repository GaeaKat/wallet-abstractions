
// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_VERTEX
#define ABSTRACTIONS_REDEEM_VERTEX

#include <abstractions/transaction.hpp>
#include <abstractions/redeem/redeem.hpp>

namespace abstractions::redeem {
    template <typename in, typename out>
    struct vertex : abstractions::vertex<in, out> {
        using parent = abstractions::vertex<in, out>;
        using parent::vertex;
        
        satoshi redeemed() const {
            return fold([](satoshi v, in x)->satoshi{
                return value(x) + v;
            }, satoshi{0}, vertex::Inputs);
        }
        
        int fee() const {
            return [](satoshi r, satoshi s)->satoshi{if (s > r) return 0; return r - s;}(redeemed(), vertex::spent());
        } 
        
        bool valid() const {
            return fee() >= 0;
        }
        
        bytes write() const;
    };
    
} 

#endif
