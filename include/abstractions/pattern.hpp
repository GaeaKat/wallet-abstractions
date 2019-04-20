#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <data/crypto/keypair.hpp>
#include <abstractions/machine.hpp>

namespace abstractions {
    
    namespace pattern {
        
        namespace abstract {
        
            template <
                typename Key,
                typename Script, 
                typename Tx, 
                typename Machine
            > struct basic : 
                public virtual machine::definition<Machine, Script, Tx> {
                
                // make a script pubkey. 
                virtual Script pay(Key) const = 0;
                
                // make a script signature.
                virtual Script redeem(Key, Tx) const = 0;
                
                void pattern_definition(Key k, Tx t, Machine i) const final {
                    assert(i.run(pay(k), redeem(k, t), t));
                }
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag, 
                typename Tx, 
                typename Machine
            > struct tagged : public virtual basic<Key, Machine, Script, Tx> {
                
                virtual Tag tag(Key) const = 0;
                
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag, 
                typename Tx, 
                typename Machine
            > struct recognizable : public virtual tagged<Key, Machine, Tag, Script, Tx> {
                
                virtual bool recognize(Script, Tag) const = 0;
                
                void recognizable_pattern_definition(Key k) const final {
                    assert(recognize(basic<Key, Machine, Script, Tx>::pay(k),
                                     tagged<Key, Machine, Tag, Script, Tx>::tag(k)));
                }
                
            };
        
            template <
                typename Key,
                typename Script, 
                typename Tag, 
                typename Tx, 
                typename Machine
            > struct addressable : public virtual tagged<Key, Machine, Tag, Script, Tx> {
                
                virtual Script pay(Tag) const = 0;
                
                Script pay(Key k) const final override {
                    return pay(tagged<Key, Machine, Tag, Script, Tx>::tag(k));
                }
                
            };
            
            template <
                typename Sk,
                typename Pk, 
                typename Script, 
                typename Tag, 
                typename Tx, 
                typename Machine
            > struct standard : public virtual data::crypto::keypair<Sk, Pk>, 
                public recognizable<Sk, Machine, Tag, Script, Tx>, 
                public addressable<Sk, Machine, Tag, Script, Tx> {
                    
                virtual Tag tag(Pk) const = 0;
                
                Tag tag(Sk k) const final override {
                    return tag(data::crypto::to_public<Sk, Pk>{}(k));
                };
            };
            
        }
        
        template <
            typename Sk, 
            typename Pk, 
            typename Script, 
            typename Pay, 
            typename Redeem, 
            typename Recognize, 
            typename Tx, 
            typename Machine
        > struct pay_to_public_key final : public abstract::standard<Sk, Pk, Script, Pk, Tx, Machine> {
            
            Pk tag(Pk k) const final override {
                return k;
            };
            
            Script pay(Pk k) const final override {
                return Pay{}(k);
            };
            
            Script redeem(Sk k, Tx t) const final override {
                return Redeem{}(k, t);
            }
            
            bool recognize(Script s, Pk k) const final override {
                return Recognize{}(s, k);
            };
        
        };
        
        template <
            typename Sk, 
            typename Pk, 
            typename Script, 
            typename Address, 
            typename Pay, 
            typename Redeem, 
            typename Recognize, 
            typename Hash, 
            typename Tx, 
            typename Machine
        > struct pay_to_address final : public abstract::standard<Sk, Pk, Script, Address, Tx, Machine> {
            
            Address tag(Pk k) const final override {
                return Hash{}(k);
            };
            
            Script pay(Address a) const final override {
                return Pay{}(a);
            };
            
            Script redeem(Sk k, Tx t) const final override {
                return Redeem{}(k, t);
            }
            
            bool recognize(Script s, Hash k) const final override {
                return Recognize{}(s, k);
            };
        
        };
        
    }
    
} 

#endif
