#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"

namespace abstractions 
{
    namespace redeem
    {        
        template<typename truth>
        struct knowledge {
            ℕ Category;
            truth Observed;
        };
        
        template<
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename truth,          // cases that we know how to redeem. 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<input_script, outpoint, output_script, knowledge<truth>, will> {
            using logos = redeemer<input_script, outpoint, output_script, knowledge<truth>, will>;
            using action = typename logos::thought;
                
            vector<ℕ> moves;
                
            mind(vector<ℕ> m) : moves(m) {}
                
            virtual action act(ℕ essence, ℕ act) const = 0;
            
            virtual bool could(ℕ form, will outcome, truth matter, ℕ motion) const = 0;

            action how(will outcome, truth known) const final override {
                for (ℕ move : moves) 
                    if (could(known.Category, outcome, known.Observed, move)) 
                        return act(known.Category, move);
                return nullptr;
            }
        };
        
        template<typename power, typename function, typename knowledge>
        using satisfies = bool (*)(function, power, knowledge);
        
        template<typename power, typename function, typename knowledge>
        struct deed : posession<function, knowledge> {
            // A power exists that will cause this function to return true.
            const satisfies<function, power, knowledge> Existence;
            
            bool valid() const {
                return Existence != nullptr;
            }
            
            deed(function output, knowledge claim) : Existence(nullptr), posession<function, knowledge>(output, claim) {}
            deed(
                satisfies<function, power, knowledge> existence, 
                power magic, 
                function output,
                knowledge claim) : Existence(existence(magic, output, claim) ? existence : nullptr), posession<function, knowledge>(output, claim) {}
        };
    
    } // redeem
    
} // abstractions

#endif
