// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <abstractions/redeem.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>
    tx redeem(list<pattern::abstract::recognizable<key, script, tag, tx, machine>&> patterns, vertex<key, out, point> v) noexcept {
        using pattern = pattern::abstract::recognizable<key, script, tag, tx, machine>&;
        using vertex = vertex<key, out, point>;
        using input = typename input<point, script>::representation;
        
        tx invalid{v.write()};
        
        list<input> inputs = {};
        for(typename vertex::spendable s : v.Inputs) {
            input in{};
            for (pattern p : patterns) {
                list<tag> tags = p.recognize(s.Output.script());
                if (tags.empty()) continue;
                in = p.redeem(s.Output, invalid, s.Key);
            }
            if (!in.Valid) return {};
            inputs = inputs + in;
        }
        
        return tx{inputs, v.Outputs};
    };
    
}
