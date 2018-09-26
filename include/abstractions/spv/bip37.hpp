#ifndef ABSTRACTIONS_SPV_BIP37_HPP
#define ABSTRACTIONS_SPV_BIP37_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/blockchain/merkle.hpp>

namespace abstractions {
    
    namespace merkle {
        
        const int digest_size = 32;
        
        using digest = std::array<byte, digest_size>;
        
        list<proof<digest>> parse_partial(N size, bytestring b);
        
    }
    
}

#endif 
