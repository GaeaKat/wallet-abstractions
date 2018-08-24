#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"
#include "observe.hpp"
#include "could.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template <typename script, typename outpoint, typename tag, typename will>
        struct association;
        
        template <typename script, typename outpoint, typename tag, typename will>
        struct concept {
            knowledge What;
            
            // The pattern which this script matches. 
            const pattern<script> Match;
            
            // The tags associated with this pattern. 
            const vector<tag> Tags;
            
        private:
            concept() : What(impossible), Match(nullptr) {}
            
            friend association<script, outpoint, tag, will>;
        };
        
        template <typename script, typename outpoint, typename tag, typename will>
        struct association {
            // The pattern which this script matches. 
            const pattern<script> Match;
            
            // The tags associated with this pattern. 
            const tags<tag, script> Tags;
            
            const concept<script, outpoint, tag, will> think(script output, will outcome) {
                if (!Match(output)) return concept<script, outpoint, tag, will>();
                
                
            }
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint> imagine(pattern<script>, vector<tag>, will) const = 0;
        };

        template<
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename tag, 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<script, outpoint, will> {
            using thought = thought<script, outpoint>;
            using association = association<script, outpoint, tag, will>;
            using concept = concept<script, outpoint, tag, will>;
            using theory = vector<const association&>;
            
            theory brain;

            mind(theory b) : brain(b) {}

            thought what(script output, will outcome) const final override {
                for (association cognition : brain) {
                    concept idea = cognition.think(output);
                    if (idea.What == impossible) continue;
                    
                    return cognition.imagine(idea.Tags, idea.What);
                    
                    if (idea.Concept.Match(output)) {
                        vector<tag> tags = idea.Concept.Tags(output);
                        return idea.imagine(tags, idea.what(output, tags), outcome);
                    }
                }
                
                return nullptr;
            }
        };
        
        template <typename secret, typename script, typename outpoint, typename tag, typename will>
        struct memory : association<script, outpoint, tag, will> {
            const database<secret, tag>& d; 
            
            
        };
        
        template <typename secret, typename script, typename outpoint, typename tag, typename will>
        struct single : public concept<script, outpoint, tag, will> {
            const pattern<script> Match;
            
            // What tags are associated with this pattern? 
            const tags<tag, script> Tags;
            
            // Could we achieve the given outcome if we have the 
            // secret information used to produce the given tags? 
            //knowledge how(script, will, vector<tag>) const = 0;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint> imagine(vector<tag>, will) const = 0;
        };
        
        template <typename secret, typename script, typename outpoint, typename tag, typename will>
        struct multiple : public concept<script, outpoint, tag, will> {
            const pattern<script> Match;
            
            // What tags are associated with this pattern? 
            const tags<tag, script> Tags;
            
            // Could we achieve the given outcome if we have the 
            // secret information used to produce the given tags? 
            //knowledge how(script, will, vector<tag>) const = 0;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint> imagine(vector<tag>, will) const = 0;
        };
    
    } // redeem
    
} // abstractions

#endif
