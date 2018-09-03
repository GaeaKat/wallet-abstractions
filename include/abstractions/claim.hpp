#ifndef ABSTRACTIONS_CLAIM_HPP
#define ABSTRACTIONS_CLAIM_HPP

#include "one_way.hpp"

namespace abstractions
{
    
    template <typename S, typename P>
    struct claim {
        P SuchThat;
        one_way<S, P> Exists;
        
        bool verify(S proof) const {
            return satisfies(Exists, proof, SuchThat);
        }
        
        claim(P r, one_way<S, P> f) : SuchThat(r), Exists(s) {}
    };
    
    template <typename S, typename P>
    struct stake : public claim<S, P> {        
        S Proof;
        
        bool valid() const {
            return verify(Proof);
        }
        
        stake(S p, P r, one_way<S, P> f) : claim<S, P>(r, f), Proof(p) {}
    };

}

#endif

