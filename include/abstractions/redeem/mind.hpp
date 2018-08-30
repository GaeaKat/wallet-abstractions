#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"
#include "observe.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template <typename script, typename outpoint, typename output, typename tag, typename will>
        struct association {
            const pattern<script> Match;
            
            // What tags are associated with this pattern? 
            const tags<tag, script> Tags;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            virtual thought<script, outpoint, output> imagine(vector<tag>, will) const = 0;
            
            association(pattern<script> match, tags<tag, script> tags) : Match(match), Tags(tags) {}
        };

        // mind is concerned with matching the correct rules to 
        // a given output pattern. 
        template<
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output,
            typename tag, 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<script, outpoint, output, will> {
            using thought = thought<script, outpoint, output>;
            using association = association<script, outpoint, output, tag, will>;
            using theory = vector<association>;
            
            theory brain;

            mind(theory b) : brain(b) {}

            thought what(script pubkey, will outcome) const final override {
                for (association concept : brain)
                    if (concept.Match(pubkey)) 
                        return concept.imagine(concept.Tags(pubkey), outcome);

                return nullptr;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
