#ifndef ABSTRACTIONS_SPV_BIP37_HPP
#define ABSTRACTIONS_SPV_BIP37_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/bytestring.hpp>
#include <abstractions/blockchain/merkle.hpp>

namespace abstractions {
    
    namespace merkle {
        
        const int digest_size = 32;
        
        using digest = std::array<byte, digest_size>;
        
        using partial_tree_encoded = bytestring;
        
        partial_tree<digest> parse_partial(N size, partial_tree_encoded b);
        
    }
    
}

#endif 
