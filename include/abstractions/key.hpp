#ifndef ABSTRACTIONS_KEY_HPP
#define ABSTRACTIONS_KEY_HPP

#include "abstractions.hpp"

namespace abstractions
{

    template <typename P>
    extern const P zero_pubkey;
        
    template <typename S>
    extern const S zero_secret;
    
    template <typename S, typename P>
    using to_public = P (* const)(S);
        
    template <typename S, typename P>
    struct key {
        S Secret;
        P Pubkey;
        to_public<S, P> ToPublic;
        
        bool valid() const {
            return ToPublic != nullptr && Secret != zero_secret<S> && Pubkey != zero_pubkey<P> && Pubkey == ToPublic(Secret);
        }
            
        key() : Secret(zero_secret<S>), Pubkey(zero_pubkey<P>), ToPublic(nullptr) {}
        key(S s, P p, to_public<S, P> tp) : Secret(s), Pubkey(p), ToPublic(tp) {}
    };

}

#endif
