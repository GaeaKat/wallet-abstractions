// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/script.hpp>

namespace abstractions::script {
    
    bytes program::compile() const {
        bytes b{static_cast<unsigned char>(length())};
        data::writer s{b};
        write(s);
        return b;
    };
}
