#ifndef ABSTRACTIONS_KEY_HPP
#define ABSTRACTIONS_KEY_HPP

#include "inverse.hpp"

namespace abstractions
{
    
    // proofs and claims concerning public and private keys. 
    namespace key {
        template <typename f, typename priv, typename pub>
        using claim_exists_private = inverse::claim<f, priv, pub>;
        
        template <typename f, typename priv, typename pub>
        using proof_exists_private = inverse::proof<f, priv, pub>;
        
        template <typename f, typename priv, typename pub>
        struct pubkey {
            f ToPublic;
            pub Pubkey;
            
            // claim that a secret key exists which produces this public key.
            claim_exists_private<f, priv, pub> claim() {
                return claim_inverse(ToPublic, Pubkey);
            }
            
            pubkey(f to_public, pub p) : ToPublic{to_public}, Pubkey{p} {}
            
        };
        
        template <typename f, typename priv, typename pub>
        struct pair : public pubkey<f, priv, pub> {
            using parent = pubkey<f, priv, pub>;
            
            priv Secret;
            
            // prove that the secret exists. 
            proof_exists_private<f, priv, pub> claim() {
                return prove_inverse(parent::ToPublic, parent::Pubkey, Secret);
            }
            
            pub pubkey() const {
                return parent::Pubkey;
            }
            
            priv secret() const {
                return Secret;
            }
            
            pair(f to_public, pub p, priv s) : parent{to_public, p}, Secret{s} {}
            
        };
        
    }

}

#endif
