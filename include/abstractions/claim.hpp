#ifndef ABSTRACTIONS_CLAIM_HPP
#define ABSTRACTIONS_CLAIM_HPP

#include "abstractions.hpp"

namespace abstractions
{
    template <typename S, typename P>
    struct claim {
        P Right;
        satisfies<S, P> Satisfies;
        
        bool verify(S s, knowledge property) const {
            return property == (property | Satisfies(s, Right));
        }
        
        claim(P r, satisfies<S, P> s) : Right(r), Satisfies(s) {}
    };
    
    template <typename S, typename P>
    struct asset : public claim<S, P> {        
        S Proof;
        
        bool valid(knowledge property) const {
            return verify(Proof, property);
        }
        
        asset(S p, P r, satisfies<S, P> s) : asset<S, P>(r, s), Proof(p) {}
    };

}

#endif

