#ifndef ABSTRACTIONS_DATABASE_HPP
#define ABSTRACTIONS_DATABASE_HPP

#include "key.hpp"
#include "map.hpp"

namespace abstractions
{
    
    namespace tags
    {
        
        template <typename F, typename tag, typename to_public, typename secret, typename pub>
        struct tagged_pubkey {
            F Function;
            
            // The tag which is is produced by the public key. 
            tag Tag;
            
            key::pubkey<to_public, secret, pub> Pubkey;
            
            inverse::proof<F, pub, tag> TagProof;
            
            key::proof<to_public, secret, pub> KeyClaim;
            
            bool validate() const {
                return Function == TagProof.Exist.Function
                    && Tag == TagProof.Proposition
                    && Pubkey.ToPublic == KeyClaim.Exist.Function
                    && Pubkey.Pubkey == TagProof.Derivation
                    && Pubkey.Pubkey == KeyClaim.Proposition;
            }
            
            bool verify() const {
                return validate() && TagProof.verify();
            }
            
        };
    
        template <typename F, typename tag, typename to_public, typename secret, typename pub>
        struct tagged_secret {
            F Function;
            
            // The tag which is is produced by the public key. 
            tag Tag;
            
            // the keypair
            key::pair<to_public, secret, pub> Keypair;
            
            inverse::proof<F, pub, tag> TagProof;
            
            key::proof<to_public, secret, pub> KeyProof;
            
            bool validate() const {
                return Function == TagProof.Exist.Function
                    && Tag == TagProof.Proposition
                    && Keypair.ToPublic == KeyProof.Exist.Function
                    && Keypair.Pubkey == TagProof.Derivation
                    && Keypair.Pubkey == KeyProof.Proposition
                    && Keypair.Secret == KeyProof.Derivation;
            }
            
            bool verify() const {
                return validate() && KeyProof.verify() && TagProof.verify();
            }
            
            tagged_pubkey<to_public, secret, pub, F, tag> pubkey() {
                return {Function, Tag, key::pubkey<to_public, secret, pub>{Keypair.ToPublic, Keypair.Public}, TagProof, KeyProof.make_claim()};
            }
            
        };
        
    }
    
}

#endif
