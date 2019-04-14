#ifndef ABSTRACTIONS_KEY_HPP
#define ABSTRACTIONS_KEY_HPP

#include <data/knowledge/inverse.hpp>
#include <data/crypto/concepts.hpp>

namespace abstractions {
    
    // proofs and claims concerning public and private keys. 
    namespace key {
        template <typename priv, typename pub>
        using to_public = ::data::crypto::keypair<priv, pub>;
        
        template <typename priv, typename pub>
        struct claim : virtual data::knowledge::inverse::claim<to_public<priv, pub>, priv, pub> {
            using parent = data::knowledge::inverse::claim<to_public<priv, pub>, priv, pub>;
            
            pub pubkey() const {
                return parent::SuchThat;
            }
            
            claim(pub p) : parent{to_public<priv, pub>{}, p} {}
        };
        
        template <typename priv, typename pub>
        struct pair :
            public claim<priv, pub>,
            public data::knowledge::inverse::proof<to_public<priv, pub>, priv, pub> {
            using proof = data::knowledge::inverse::proof<to_public<priv, pub>, priv, pub>;
            
            priv secret() const {
                return proof::Derivation;
            }
            
            pair(pub p, priv s) : proof{to_public<priv, pub>{}, p, s} {}
        };
        
    }

}

#endif
