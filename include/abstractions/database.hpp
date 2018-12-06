#ifndef ABSTRACTIONS_DATABASE_HPP
#define ABSTRACTIONS_DATABASE_HPP

#include "key.hpp"
#include "map.hpp"

namespace abstractions
{
    
    namespace database
    {
        
        template <typename Mtp, typename Mps, typename tag, typename pubkey, typename secret, typename F, typename to_public>
        struct tag_map {
            static const map::definition::map<Mtp, tag, inverse::proof<F, pubkey, tag>> r1{};
            static const map::definition::map<Mps, pubkey, key::proof<to_public, secret, pubkey>> r2{};
            static const map::definition::map<tag_map, tag, tagged_key<to_public, secret, pubkey, F, tag>> r3{};
            
            F Function;
            
            to_public ToPublic;
            
            Mtp TagsToPubkeys;
            
            Mps PubkeysToPrivkeys;
        
            bool empty() const {
                return map::empty(TagsToPubkeys);
            }
            
            tagged_key<to_public, secret, pubkey, F, tag> operator[](tag t) {
                auto TagProof = TagsToPubkeys[t];
                auto KeyProof = PubkeysToPrivkeys[TagProof.Proposition];
                return tagged_key<to_public, secret, pubkey, F, tag>{Function, t, key::pair{KeyProof}, TagProof, KeyProof};
            }
            
            tag_map insert(tag t, tagged_key<to_public, secret, pubkey, F, tag> e) {
                if (e.Tag != t || !e.validate()) return {};
                return {Function, ToPublic, TagsToPubkeys.insert(t, e.TagProof), PubkeysToPrivkeys.insert(t, e.KeyProof)};
            }
            
            tag_map remove(tag t) {
                return {Function, ToPublic, TagsToPubkeys, TagsToPubkeys.remove(t), PubkeysToPrivkeys};
            }
        };
        
        // Given a map of claims about public keys, given a set of patterns, and
        // given an output, return a claim that a private key exists which can
        // redeem the output if 
        
    }
    
}

#endif
