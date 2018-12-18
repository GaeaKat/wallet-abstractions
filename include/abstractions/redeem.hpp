#ifndef ABSTRACTIONS_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_HPP

#include <abstractions/pattern.hpp>
#include <abstractions/bitcoin/script.hpp>
#include <abstractions/tags.hpp>

namespace abstractions 
{

    template <typename scr, typename outpoint, typename tx>
    struct spendible {
        N Value;
        scr Output;
        outpoint Outpoint;
        
        virtual scr redeem(bitcoin::script::input_index<tx>) const = 0;
    };
    
    template <typename script, typename outpoint, typename tx, typename keypair, typename pattern>
    struct source {
        struct spendable : public spendible<script, outpoint, tx> {
            using parent = spendible<script, outpoint, tx>; 
            
            keypair Keypair;
            pattern Pattern;

            script redeem(bitcoin::script::input_index<tx> t) const {
                return Pattern.redeem(parent::Output, t, Keypair);
            }
        };
        
        virtual list<spendable> spend(N value) = 0;
    };

    // represents an incomplete tx that hasn't been signed yet. 
    template <typename scr, typename outpoint, typename tx, typename output>
    struct vertex {
        list<spendible<scr, outpoint, tx>> Inputs;
        list<output> Outputs;
        
        N spent() {
            // TODO
        }
        
        N fee() {
            // TODO
        }
        
        tx redeem() const {
            struct redeem_input{
                tx Transaction;
        
                struct input {
                    outpoint Outpoint;
                    scr Script;
                };
                
                input operator()(N index, spendible<scr, outpoint, tx> s) const {
                    return input{s.Outpoint, s.redeem(bitcoin::script::input_index<tx>{Transaction, index})};
                }
            };
            
            return tx{map_indexed(redeem_input{tx{Outputs}}, Inputs), Outputs};
        }
        
    };
    
} 

#endif
