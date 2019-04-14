#ifndef ABSTRACTIONS_VERTEX
#define ABSTRACTIONS_VERTEX

#include <abstractions/pattern.hpp>
#include <abstractions/bitcoin/script.hpp>
#include <abstractions/tags.hpp>
#include <abstractions/data.hpp>

namespace abstractions {

    // represents an incomplete tx that hasn't been signed yet. 
    template <typename digest, typename priv, typename pub, typename tx, typename output>
    struct vertex {
        struct input {
            spendable<digest, priv, pub> Spendable;
            output Prevout;
        };
        
        list<input> Inputs;
        list<output> Outputs;
        
        N spent() const {
            return data::reduce([](input i){return bitcoin::output::value(i.Prevout);}, Inputs);
        }
        
        N sent() const {
            return data::reduce([](output o){return bitcoin::output::value(o);}, Outputs);
        }
        
        N fee() const {
            return spent() - sent();
        }
        
        tx redeem() const {
            struct redeem_input{
                tx Transaction;
        
                struct input {
                    bitcoin::outpoint<digest> Outpoint;
                    pattern::script Script;
                };
                
                input operator()(N index, spendable<digest, priv, pub> s) const {
                    return input{s.Outpoint, s.redeem(bitcoin::script::input_index<tx>{Transaction, index})};
                }
            };
            
            return tx{map_indexed(redeem_input{tx{Outputs}}, Inputs), Outputs};
        }
        
    };
    
} 

#endif
