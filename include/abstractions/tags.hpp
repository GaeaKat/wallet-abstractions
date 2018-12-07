#ifndef ABSTRACTIONS_TAGS_HPP
#define ABSTRACTIONS_TAGS_HPP

#include <abstractions/data/map.hpp>
#include "key.hpp"

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
        
        template <typename Mtp, typename Mps, typename tag, typename pubkey, typename secret, typename F, typename to_public>
        struct tag_map {
            constexpr static const data::map::definition::map<Mtp, tag, inverse::proof<F, pubkey, tag> > r1{};
            constexpr static const data::map::definition::map<Mps, pubkey, key::proof<to_public, secret, pubkey> > r2{};
            constexpr static const data::map::definition::map<tag_map, tag, tagged_secret<to_public, secret, pubkey, F, tag> > r3{};
            
            F Function;
            
            to_public ToPublic;
            
            Mtp TagsToPubkeys;
            
            Mps PubkeysToPrivkeys;
        
            bool empty() const {
                return data::map::empty(TagsToPubkeys);
            }
            
            tagged_secret<to_public, secret, pubkey, F, tag> operator[](tag t) {
                auto TagProof = TagsToPubkeys[t];
                auto KeyProof = PubkeysToPrivkeys[TagProof.Proposition];
                return tagged_secret<to_public, secret, pubkey, F, tag>{Function, t, key::pair{KeyProof}, TagProof, KeyProof};
            }
            
            tag_map insert(tag t, tagged_secret<to_public, secret, pubkey, F, tag> e) {
                if (e.Tag != t || !e.validate()) return {};
                return {Function, ToPublic, TagsToPubkeys.insert(t, e.TagProof), PubkeysToPrivkeys.insert(t, e.KeyProof)};
            }
            
            tag_map remove(tag t) {
                return {Function, ToPublic, TagsToPubkeys, TagsToPubkeys.remove(t), PubkeysToPrivkeys};
            }
        };
        
    }
    
}

#endif
