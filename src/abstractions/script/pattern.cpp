// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/pattern.hpp>

namespace abstractions::script {
    
    bool pattern::match(queue<element> e, program p) {
        if (e.empty() && p.empty()) return true;
        if (!e.empty() || !p.empty()) return false;
        if (!e.first().match(p.first())) return false;
        return match(e.rest(), p.rest());
    }
}


