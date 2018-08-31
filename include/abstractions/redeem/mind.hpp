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
        
        template <typename script, typename outpoint, typename output, typename tag, typename will>
        using theory = vector<association<script, outpoint, output, tag, will>>;

        // mind is concerned with matching the correct rules to 
        // a given output pattern. 
        template<
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output,
            typename tag, 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<script, outpoint, output, will> {
            using brain = theory<script, outpoint, output, tag, will>;
            using idea = association<script, outpoint, output, tag, will>;
            
            brain Brain;

            mind(
                brain b, 
                output_value<output> ov,
                output_script<output, script> os,
                prepend_script<script> p,
                blockchain<script, outpoint>& bcx) : redeemer<script, outpoint, output, will>(ov, os, p, bcx), Brain(b) {}

            thought<script, outpoint, output> how(script pubkey, will outcome) const final override {
                for (idea concept : Brain)
                    if (concept.Match(pubkey)) 
                        return concept.imagine(concept.Tags(pubkey), outcome);

                return nullptr;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
