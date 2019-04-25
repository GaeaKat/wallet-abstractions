// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_REDEEM
#define ABSTRACTIONS_REDEEM

#include <abstractions/pattern.hpp>
#include <abstractions/data.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    // A vertex is simply a transaction without input scripts. 
    // In other words, it represents a transaction that can
    // be signed to generate input scripts. 
    template <typename key, typename out, typename point>
    struct vertex {
    
        struct spendable {
            key Key;
            out Output;
            point Point;
            
            bool valid() const;
        };
    
        list<spendable> Inputs;
        list<out> Outputs;
        
        vertex(list<spendable> i, list<out> o) : Inputs{i}, Outputs{o} {}
        vertex(std::initializer_list<spendable>, std::initializer_list<out>);
        
    };
    
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>
    tx redeem(list<pattern::abstract::recognizable<key, script, tag, tx, machine>&>, vertex<key, out, point>);
    
}

#endif
