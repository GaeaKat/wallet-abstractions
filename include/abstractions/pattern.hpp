// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <abstractions/crypto/address.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    template <typename Tx>
    struct input_index{
        Tx Transaction;
        index Index;
    };
    
    namespace pattern {
        template <typename Script> using output = output<Script>;
        namespace interface {
            
            template <
                typename Key,
                typename Script, 
                typename Tx>
            struct redeemer {
                // make a script signature. 
                virtual Script redeem(output<Script>, input_index<Tx>, const Key&) const = 0;
            };
        
            template <
                typename Key,
                typename Script>
            struct payable {
                // make a script pubkey. 
                virtual Script pay(const Key&) const = 0;
            };
        
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tx>
            struct pattern : 
                public data::crypto::keypair<Sk, Pk>, 
                public redeemer<Sk, Script, Tx>, 
                public virtual payable<Pk, Script> {
                using payable<Pk, Script>::pay;
                using redeemer<Sk, Script, Tx>::redeem;
                
                // make a script pubkey. 
                Script pay(const Sk& k) const {
                    return pay(data::crypto::to_public<Sk, Pk>{}(k));
                };
                
                template <typename Machine>
                void pattern_definition(output<Script> o, input_index<Tx> i, const Sk& k, Machine m) const {
                    assert(m.run(pay(k), redeem(o, i, k), i.Transaction));
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
                public pattern<Sk, Pk, Script, Tx>, 
                public addressable<Sk, Script, Tag>, 
                public addressable<Pk, Script, Tag>, 
                public recognizable<Pk, Script, Tag> {
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
                public pattern<Sk, Pk, Script, Tx>, 
                public addressable<Sk, Script, Pk>, 
                public recognizable<Pk, Script, Pk> {
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
