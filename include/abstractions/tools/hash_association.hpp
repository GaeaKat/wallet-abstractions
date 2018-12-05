#ifndef ABSTRACTIONS_TOOLS_HASH_ASSOCIATION
#define ABSTRACTIONS_TOOLS_HASH_ASSOCIATION

#include <abstractions/association.hpp>

namespace abstractions {
    
    namespace tools {
        
        // turn an association by a hash of a thing into an association of that thing. 
        template <typename key, typename digest, typename value>
        class hash_association : association<key, value> {
            association<digest, value>& map;
            
            const value operator[](key k) const final override {
                return map[hash(k)];
            };
        };

    }

}

#endif
