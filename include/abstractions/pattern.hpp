#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <data/crypto/keypair.hpp>
#include <abstractions/machine.hpp>

namespace abstractions {
    
    namespace pattern {
    
        template <
            typename Key,
            typename Script, 
            typename Tx, 
            typename Interpreter
        > struct basic : 
            public machine::definition<Interpreter, Script, Tx> {
            
            // make a script pubkey. 
            virtual Script pay(Key) const = 0;
            
            // make a script signature.
            virtual Script redeem(Key, Tx) const = 0;
            
            void pattern_definition(Key k, Tx t, Interpreter i) {
                assert(i.run(pay(k), redeem(k, t), t));
            }
        };
    
        template <
            typename Key,
            typename Script, 
            typename Data, 
            typename Tx, 
            typename Interpreter
        > struct tagged : public basic<Key, Interpreter, Script, Tx> {
            
            virtual Data tag(Key) const = 0;
            
        };
    
        template <
            typename Key,
            typename Script, 
            typename Data, 
            typename Tx, 
            typename Interpreter
        > struct recognizable : public tagged<Key, Interpreter, Data, Script, Tx> {
                
            virtual bool recognize(Script, Data) const = 0;
                
            void recognizable_pattern_definition(Key k) {
                assert(recognize(basic<Key, Interpreter, Script, Tx>::pay(k),
                                tagged<Key, Interpreter, Data, Script, Tx>::tag(k)));
            }
            
        };
    
        template <
            typename Key,
            typename Script, 
            typename Data, 
            typename Tx, 
            typename Interpreter
        > struct addressable : public tagged<Key, Interpreter, Data, Script, Tx> {
            
            virtual Script pay(Data) const = 0;
            
            void recognizable_pattern_definition(Key k) {
                assert(pay(tagged<Key, Interpreter, Data, Script, Tx>::tag(k)) == basic<Key, Interpreter, Script, Tx>::pay(k));
            }
            
        };
        
    }
    
} 

#endif
