#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"
#include <abstractions/observe.hpp>

namespace abstractions 
{
    namespace redeem
    {
        template <typename script, typename outpoint, typename out, typename tag, typename will>
        struct association {
            const pattern<script> Match;
            
            // What tags are associated with this pattern? 
            const tags<tag, script> Tags;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            virtual thought<script, outpoint, out> imagine(vector<tag>, will) const = 0;
            
            association(pattern<script> match, tags<tag, script> tags) : Match(match), Tags(tags) {}
        };
        
        template <typename script, typename outpoint, typename out, typename tag, typename will>
        using theory = vector<association<script, outpoint, out, tag, will>>;

        // mind is concerned with matching the correct rules to 
        // a given output pattern. 
        template<
            typename tx, 
            typename script,         // means of redemption. 
            typename point,       // way if indexing a previous output. 
            typename out,
            typename tag, 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<tx, script, point, out, will> {
            using brain = theory<script, point, out, tag, will>;
            using idea = association<script, point, out, tag, will>;
            
            brain Brain;

            mind(
                output::value<out> ov,
                output::script<out, script> os,
                transaction::outputs<tx, out> gou, 
                transaction::outpoints<tx, point> goi, 
                transaction::input_scripts<tx, point, script> gs, 
                prepend_script<script> p,
                blockchain<script, point>& bcx, 
                brain b) : redeemer<tx, script, point, out, will>(ov, os, gou, goi, gs, p, bcx), Brain(b) {}

            thought<script, point, out> how(script pubkey, will outcome) const final override {
                for (idea concept : Brain)
                    if (concept.Match(pubkey)) 
                        return concept.imagine(concept.Tags(pubkey), outcome);

                return nullptr;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
