// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <abstractions/redeem.hpp>

namespace abstractions {
    
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>
    tx redeem(list<pattern::abstract::recognizable<key, script, tag, tx, machine>&>, vertex<key, out, point>) {
        throw 0;
    }
    
}
