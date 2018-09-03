#ifndef ABSTRACTIONS_FUNDAMENTAL_HPP
#define ABSTRACTIONS_FUNDAMENTAL_HPP

#include <vector>
#include <memory>
#include <string>

namespace abstractions 
{
    
    template<typename X>
    using vector = const std::vector<X>;

    using byte = uint8_t;

    using bytestring = const vector<byte>;

    template<typename X>
    using pointer = const std::shared_ptr<X>;

    using string = const std::string;

    using knowledge = const uint64_t; 

}

#endif
