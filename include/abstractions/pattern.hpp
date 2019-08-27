// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <abstractions/crypto/address.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    namespace pattern {
        
        namespace abstract {
        
            template <
                typename Key,
                typename Script, 
                typename Tx>
            struct redeemer {
                // make a script signature. 
                virtual Script redeem(satoshi, Script, const Tx&, index, const Key&) const = 0;
            };
        
            template <
                typename Key,
                typename Script>
            struct payable {
                // make a script pubkey. 
                virtual Script pay(const Key&) const = 0;
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tx>
            struct pattern : 
                public redeemer<Key, Script, Tx>, 
                public virtual payable<Key, Script> {
                using payable<Key, Script>::pay;
                
                template <typename Machine>
                void pattern_definition(const Key& k, const Tx& t, Machine i) const {
                    assert(i.run(pay(k), redeem(k, t), t));
                }
            };
        
            template <
                typename Key, 
                typename Script, 
                typename Tag> 
            struct tagged : public virtual payable<Tag, Script> {
                // Tag is what we use to recognize an output. 
                virtual Tag tag(const Key&) const = 0;
            };
        
            template <
                typename Key, 
                typename Script, 
                typename Tag> 
            struct addressable : 
                public virtual tagged<Key, Script, Tag>, 
                public virtual payable<Key, Script> {
                using tagged<Key, Script, Tag>::tag;
                using tagged<Key, Script, Tag>::pay;
                
                virtual Script pay(const Key& k) const final override {
                    return pay(tag(k));
                };
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag>
            struct recognizable : public virtual tagged<Key, Script, Tag> {
                using tagged<Key, Script, Tag>::tag;
                using tagged<Key, Script, Tag>::pay;
                
                virtual list<Tag> recognize(Script) const = 0;
                
                void recognizable_pattern_definition(const Tag& k) const {
                    if (tag(k) != recognize(pay(k))) throw 0;
                }
                
            };
            
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tag, 
                typename Tx>
            struct pay_to_address : 
                public pattern<Sk, Script, Tx>, 
                public addressable<Sk, Script, Tag>, 
                public addressable<Pk, Script, Tag>, 
                public recognizable<Pk, Script, Tag>, 
                public data::crypto::keypair<Sk, Pk> {
                using recognizable<Pk, Script, Tag>::tag;
                using addressable<Pk, Script, Tag>::pay;
                using addressable<Sk, Script, Tag>::pay;
                
                Tag tag(const Sk& k) const final override {
                    return tag(data::crypto::to_public<Sk, Pk>{}(k));
                };
                
            };
            
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tx>
            struct pay_to_pubkey  : 
                public pattern<Sk, Script, Tx>, 
                public addressable<Sk, Script, Pk>, 
                public recognizable<Pk, Script, Pk>, 
                public data::crypto::keypair<Sk, Pk> {
                using recognizable<Pk, Script, Pk>::tag;
                using addressable<Sk, Script, Pk>::pay;
                
                Pk tag(const Sk& k) const final override {
                    return tag(data::crypto::to_public<Sk, Pk>{}(k));
                };
                
                Pk tag(const Pk& k) const final override {
                    return k;
                };
                
            };
            
        }
        
    }
    
} 

#endif
