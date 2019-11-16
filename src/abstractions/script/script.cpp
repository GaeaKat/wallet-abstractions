// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/script.hpp>

namespace abstractions::script {
    
    // TODO there is an exception thrown here. 
    // I am not initializing the string correctly. 
    // I don't know how to do it right. 
    bytes compile(program p) {
        bytes compiled{length(p), byte{0}};
        writer{compiled} << p;
        return compiled;
    }
}
