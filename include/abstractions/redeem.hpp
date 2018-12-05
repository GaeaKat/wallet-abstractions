#ifndef ABSTRACTIONS_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_HPP

#include <abstractions/pattern.hpp>
#include <abstractions/blockchain/script.hpp>

namespace abstractions 
{
    
    template <typename scr, typename outpoint, typename tx>
    struct spendible {
        N Value;
        scr Output;
        outpoint Outpoint;
                
        virtual scr redeem(script::input_index<tx>) const = 0;
    };
        
    template <typename script, typename outpoint, typename P, typename T, typename keypair, typename pattern>
    struct source {
        struct spendable : public P {
            keypair Keypair;
            pattern Pattern;
            
            script redeem(T t) const {
                return Pattern.redeem(P::Output, t, Keypair);
            }
        };
        
        virtual list<spendable> spend(N value) = 0;
        
        virtual script change() = 0;
        
    };
    
    template <typename scr, typename outpoint, typename tx, typename output>
    struct vertex {
        list<spendible<scr, outpoint, tx>> Inputs;
        list<output> Outputs;
        
        N spent() {
            
        }
        
        N fee() {
            
        }
        
        tx redeem() const {
            struct redeem_input{
                tx Transaction;
        
                struct input {
                    outpoint Outpoint;
                    scr Script;
                };
                
                input operator()(N index, spendible<scr, outpoint, tx> s) const {
                    return input{s.Outpoint, s.redeem(script::input_index<tx>{Transaction, index})};
                }
            };
            
            return tx{map_indexed(redeem_input{tx{Outputs}}, Inputs), Outputs};
        }
        
    };
    
} 

#endif
