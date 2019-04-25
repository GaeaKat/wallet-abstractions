// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_FUNDAMENTAL
#define ABSTRACTIONS_FUNDAMENTAL

#include <vector>
#include <memory>
#include <string>

namespace abstractions {
    
    template <typename X>
    using vector = const std::vector<X>;

    using byte = uint8_t;
    
    using bytes = vector<byte>;

    template<typename X>
    using pointer = const std::shared_ptr<X>;

    using string = const std::string;

    using knowledge = const uint64_t; 
    
    using stringstream = std::stringstream;

}

#endif
