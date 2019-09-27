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
            
            template <typename...> struct pattern;
        
            template <
                typename Sk,
                typename Script, 
                typename Tx>
            struct pattern<Sk, Script, Tx> : 
                public redeemer<Sk, Script, Tx>, 
                public payable<Sk, Script> {
                using payable<Sk, Script>::pay;
                using redeemer<Sk, Script, Tx>::redeem;
                
                template <typename Machine>
                void pattern_definition(output<Script> o, input_index<Tx> i, const Sk& k, Machine m) const {
                    assert(m.run(pay(k), redeem(o, i, k), i.Transaction));
                }
            };
        
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tx>
            struct pattern<Sk, Pk, Script, Tx> : 
                public data::crypto::keypair<Sk, Pk>, 
                public pattern<Sk, Script, Tx>, 
                public payable<Pk, Script> {
                using payable<Pk, Script>::pay;
                using redeemer<Sk, Script, Tx>::redeem;
                
                // make a script pubkey. 
                Script pay(const Sk& k) const override {
                    return pay(data::crypto::to_public<Sk, Pk>{}(k));
                };
            };
        
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tag, 
                typename Tx> 
            struct tagged : public pattern<Sk, Pk, Script, Tx>, 
                public payable<Tag, Script> {
                using payable<Tag, Script>::pay;
                // Tag is what we use to recognize an output. 
                virtual Tag tag(const Pk&) const = 0;
                
                Tag tag(const Sk& k) const {
                    return tag(data::crypto::to_public<Sk, Pk>{}(k));
                };
                
                Script pay(const Pk& k) const override {
                    return pay(tag(k));
                };
            };
        
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tag, 
                typename Tx>
            struct recognizable : public tagged<Sk, Pk, Script, Tag, Tx> {
                using tagged<Sk, Pk, Script, Tag, Tx>::tag;
                using tagged<Sk, Pk, Script, Tag, Tx>::pay;
                
                virtual list<Tag> recognize(Script) const = 0;
                
                void recognizable_pattern_definition(const Tag& t) const {
                    if (tag(t) != recognize(pay(t))) throw 0;
                }
                
            };
            
        }
        
    }
    
} 

#endif
