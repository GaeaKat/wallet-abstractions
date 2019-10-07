// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_ABSTRACTIONS
#define ABSTRACTIONS_ABSTRACTIONS

#include <cstdint>
#include <memory>
#include <string>
#include <stdint.h>
#include <vector>
#include <data/data.hpp>
#include <data/stream.hpp>

#include <data/encoding/hex.hpp>
#include <data/encoding/ascii.hpp>

namespace abstractions {
    
    using index = uint32_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    using int32 = int32_t;
    
    using satoshi = uint64;
    
    using uint160 = data::uint160;
    using uint256 = data::uint256;
    using uint512 = data::uint512;
    
    template <typename X>
    using vector = std::vector<X>;

    using byte = uint8_t;
    
    using bytes = vector<byte>;

    template<typename X>
    using pointer = std::shared_ptr<X>;

    using string = const std::string;
    using hex = data::encoding::hex::string;
    using ascii = data::encoding::ascii::string;

    using knowledge = const uint64_t; 
    
    using stringstream = std::stringstream;
    using reader = data::reader;
    using writer = data::writer;
    
    using namespace data::exported;

}

#endif
