#ifndef ABSTRACTIONS_KEY_HPP
#define ABSTRACTIONS_KEY_HPP

#include "inverse.hpp"

namespace abstractions
{
    
    // proofs and claims concerning public and private keys. 
    namespace key {
        
        template <typename f, typename priv, typename pub>
        using claim = inverse::claim<f, priv, pub>;
        
        template <typename f, typename priv, typename pub>
        using proof = inverse::proof<f, priv, pub>;
        
        template <typename f, typename priv, typename pub>
        struct pubkey {
            f ToPublic;
            pub Pubkey;
            
            // claim that a secret key exists which produces this public key.
            key::claim<f, priv, pub> claim() {
                return claim_inverse(ToPublic, Pubkey);
            }
            
            pubkey(f to_public, pub p) : ToPublic{to_public}, Pubkey{p} {}
            
        };
        
        template <typename f, typename priv, typename pub>
        struct pair : public pubkey<f, priv, pub> {
            using parent = pubkey<f, priv, pub>;
            
            priv Secret;
            
            // prove that the secret exists. 
            proof<f, priv, pub> prove() {
                return prove_inverse(parent::ToPublic, parent::Pubkey, Secret);
            }
            
            pub pubkey() const {
                return parent::Pubkey;
            }
            
            priv secret() const {
                return Secret;
            }
            
            pair(f to_public, pub p, priv s) : parent{to_public, p}, Secret{s} {}
            pair(proof<f, priv, pub> p) : parent{p.Exist.Function, p.Proposition}, Secret{p.Derivation} {}
            
        };
        
    }

}

#endif
