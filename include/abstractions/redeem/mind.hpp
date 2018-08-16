#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template<typename input_script, typename outpoint, typename will>
        struct association {
            word<input_script, outpoint>* operator()(outpoint, will, knowledge) const = 0;
        };
        
        template<
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<input_script, outpoint, output_script, will> {
            using word = word<input_script, outpoint>;
            using association = association<input_script, outpoint, will>;

            map<essence, association&> brain;

            mind(map<essence, association*> theory) : brain(theory) {}

            virtual essence nature(outpoint o) const = 0;
            
            // conditions which must be satisfied hypothetically in order for
            // such a combination of 
            virtual knowledge would(essence, will) const = 0;

            word* how(outpoint o, will outcome) const final override {
                return brain[nature(o)](o, outcome, would(nature(o), outcome));
            }
        };
    
    } // redeem
    
} // abstractions

#endif
