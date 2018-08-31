#ifndef ABSTRACTIONS_LINK_HPP
#define ABSTRACTIONS_LINK_HPP

#include "observe.hpp"
#include "keypair.hpp"

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

    template<typename key, typename script, typename tag> 
    struct concept {
        pattern<script> Match;
            
        // What tags are associated with this pattern? 
        tags<tag, script> GetTags;
        
        to_public<key, tag> Tag;
    };

    template<typename key, typename out, typename script, typename tag> 
    struct link {
        out Output;
        
        concept<key, script, tag> Concept;
    };

}

#endif

