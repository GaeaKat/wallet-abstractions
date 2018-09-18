#ifndef ABSTRACTIONS_SPV_BIP37_HPP
#define ABSTRACTIONS_SPV_BIP37_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/blockchain/merkle.hpp>

namespace abstractions {

    namespace spv {
        
        using digest = const std::array<byte, 32>;
        
        
    }
    
    namespace merkle {
        
        using digest = spv::digest;
        
        list<node<digest>> parse_partial(bytestring b);
        
    }
    
}

#endif 
