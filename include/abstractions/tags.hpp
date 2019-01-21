#ifndef ABSTRACTIONS_TAGS_HPP
#define ABSTRACTIONS_TAGS_HPP

#include <abstractions/data.hpp>
#include <abstractions/key.hpp>

namespace abstractions {
    
    namespace tags {
        
        // In some cases we associate a pubkey with a tag. For example, 
        // we generate and address from the pubkey. This type keeps
        // track of the pubkey, the tag, the function which produces the
        // tag from the pubkey, and the relationship between them. 
        template <typename F, typename tag, typename priv, typename pub>
        struct pubkey {
            F Function;
            
            // The tag which is is produced by the public key. 
            tag Tag;
            
            key::pubkey<priv, pub> Pubkey;
            
            inverse::proof<F, pub, tag> TagProof;
            
            bool validate() const {
                return Function == TagProof.Exist.Function
                    && Tag == TagProof.Proposition
                    && Pubkey.Pubkey == TagProof.Derivation;
            }
            
            bool verify() const {
                return validate() && TagProof.verify();
            }
            
        };
    
        template <typename F, typename tag, typename priv, typename pub>
        struct secret {
            F Function;
            
            // The tag which is is produced by the public key. 
            tag Tag;
            
            key::pair<priv, pub> Keypair;
            
            inverse::proof<F, pub, tag> TagProof;
            
            bool validate() const {
                return Function == TagProof.Exist.Function
                    && Tag == TagProof.Proposition
                    && Keypair.Pubkey == TagProof.Derivation;
            }
            
            bool verify() const {
                return validate() && Keypair.verify() && TagProof.verify();
            }
            
            pubkey<F, tag, priv, pub> pubkey() {
                return {Function, Tag, key::pubkey<priv, pub>{Keypair.Public}, TagProof};
            }
            
        };
        
        template <typename Mtp, typename Mps, typename tag, typename pub, typename priv, typename F>
        struct map {
            constexpr static const ::data::map::definition::map<Mtp, tag, inverse::proof<F, pub, tag> > r1{};
            constexpr static const ::data::map::definition::map<Mps, pub, key::pair<priv, pub> > r2{};
            constexpr static const ::data::map::definition::map<map, tag, secret<F, tag, priv, pub> > r3{};
            
            F Function;
            
            Mtp TagsToPubkeys;
            
            Mps PubkeysToPrivkeys;
        
            bool empty() const {
                return ::data::map::empty(TagsToPubkeys);
            }
            
            secret<F, tag, priv, pub> operator[](tag t) {
                auto TagProof = TagsToPubkeys[t];
                auto KeyProof = PubkeysToPrivkeys[TagProof.Proposition];
                return secret<F, tag, priv, pub>{Function, t, key::pair<pub, priv>{KeyProof}, TagProof, KeyProof};
            }
            
            map insert(tag t, secret<F, tag, priv, pub> e) {
                if (e.Tag != t || !e.validate()) return {};
                return {Function, TagsToPubkeys.insert(t, e.TagProof), PubkeysToPrivkeys.insert(t, e.KeyProof)};
            }
            
            map remove(tag t) {
                return {Function, TagsToPubkeys, TagsToPubkeys.remove(t), PubkeysToPrivkeys};
            }
        };
        
    }
    
}

#endif
