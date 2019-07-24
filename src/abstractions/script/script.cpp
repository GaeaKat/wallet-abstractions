// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/script.hpp>

namespace abstractions::script {
    const boost::endian::order ENDIANESS=boost::endian::order::little;
    
    bytes program::compile() const {
        std::vector<byte> b{static_cast<unsigned char>(length())};
        data::slice_writer s{b,ENDIANESS};
        write(s);
        return b;
    };
}
