#ifndef ABSTRACTIONS_KEY_HPP
#define ABSTRACTIONS_KEY_HPP

#include "claim.hpp"

namespace abstractions
{
    
    // proofs and claims concerning public and private keys. 
    namespace key {
        
        template <typename to_public, typename priv, typename pub>
        struct pubkey {
            pub Pubkey;
            to_public ToPublic;
            
            // claim that a secret key exists which produces this public key.
            claim<check_inverse<to_public, priv, pub>, pub, priv> claim() {
                return claim_inverse(ToPublic, Pubkey);
            }
            
        };
        
        template <typename to_public, typename priv, typename pub>
        struct pair : public pubkey<to_public, priv, pub> {
            using parent = pubkey<to_public, priv, pub>;
            
            priv Secret;
            
            // prove that the secret exists. 
            proof<check_inverse<to_public, priv, pub>, pub, priv> claim() {
                return prove_inverse(parent::ToPublic, parent::Pubkey, Secret);
            }
            
        };
        
    }

}

#endif
