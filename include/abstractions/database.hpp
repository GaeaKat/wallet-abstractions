#ifndef ABSTRACTIONS_DATABASE_HPP
#define ABSTRACTIONS_DATABASE_HPP

#include "key.hpp"
#include "map.hpp"

namespace abstractions
{
    
    namespace database
    {
        
        template <typename to_public, typename secret, typename pubkey, typename F, typename tag>
        struct tagged_key {
            F Function;
            
            // The tag which is is produced by the public key. 
            tag Tag;
            
            // the keypair
            key::pair<to_public, secret, pubkey> Keypair;
            
            key::proof_exists_private<to_public, secret, pubkey> KeyProof;
            
            inverse::proof<F, pubkey, tag> TagProof;
            
            bool validate() const {
                return Function == TagProof.Exist.Function
                    && Tag == TagProof.Proposition
                    && Keypair.ToPublic == KeyProof.Exist.Function
                    && Keypair.Pubkey == KeyProof.Proposition
                    && Keypair.Pubkey == TagProof.Derivation
                    && Keypair.Secret == KeyProof.Derivation;
            }
            
            bool verify() const {
                return validate() && KeyProof.verify() && TagProof.verify();
            }
            
        };
        
        template <typename Mtp, typename Mps, typename tag, typename pubkey, typename secret, typename F, typename to_public>
        struct tag_map {
            static const map::definition::map<Mtp, tag, inverse::proof<F, pubkey, tag>> r1{};
            static const map::definition::map<Mps, pubkey, key::proof_exists_private<to_public, secret, pubkey>> r2{};
            
            static const map::definition::map<tag_map, tag, tagged_key<to_public, secret, pubkey, F, tag>> r3{};
            
            F Function;
            
            to_public ToPublic;
            
            Mtp TagsToPubkeys;
            
            Mps PubkeysToPrivkeys;
        
            bool empty() const {
                return map::empty(TagsToPubkeys);
            }
            
            tagged_key<to_public, secret, pubkey, F, tag> operator[](tag t) {
                return inverse::prove(Function, k, Map[k]);
            }
            
            tag_map insert(key k, inverse::proof<F, key, value> p) {
                if (k != p.SuchThat && p.Exist.Function != Function) return {};
                return {Function, Map.insert(k, p)};
            }
            
            tag_map insert(key k) {
                return {Function, Map.insert(k, Function(k))};
            }
            
            tag_map remove(tag t) {
                return {Function, ToPublic, TagsToPubkeys, Map.remove(k)};
            }
        };
        
    }
    
}

#endif
