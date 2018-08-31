#ifndef ABSTRACTIONS_KEYPAIR_HPP
#define ABSTRACTIONS_KEYPAIR_HPP

#include "abstractions.hpp"

namespace abstractions
{

    template <typename S, typename P>
    struct keypair {
        S Secret;
        P Pubkey;
        
        bool valid() const {
            return Secret.valid() && Pubkey.valid() && Pubkey == Secret.to_public();
        }
            
        keypair() : Secret(zero<S>), Pubkey(zero<P>) {}
        keypair(S s, P p) : Secret(s), Pubkey(p) {}
    };

}

#endif
