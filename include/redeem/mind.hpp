#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include<redeem/redeemer.hpp>

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
            using action = thought<input_script, outpoint>;
                
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
    
    } // redeem
    
} // abstractions

#endif
