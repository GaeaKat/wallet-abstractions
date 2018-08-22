#ifndef ABSTRACTIONS_REDEEM_MIND_HPP
#define ABSTRACTIONS_REDEEM_MIND_HPP

#include "redeemer.hpp"
#include "observe.hpp"

namespace abstractions 
{
    namespace redeem
    {
        /*template<typename script, typename tag>
        struct database : memory<tag> {
            thought<script, outpoint> retrieve(const pattern<script> Match);
        };*/
        
        template <typename script, typename outpoint, typename tag, typename will>
        struct association {
            const pattern<script> Match;
            
            // What tags are associated with this pattern? 
            const tags<tag, script> Tags;
            
            // Could we achieve the given outcome if we have the 
            // secret information used to produce the given tags? 
            //knowledge how(script, will, vector<tag>) const = 0;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint> imagine(vector<tag>, will) const = 0;
        };

        template<
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename tag, 
            typename will>           // a desired outcome. 
        struct mind : public redeemer<script, outpoint, will> {
            using thought = thought<script, outpoint>;
            using association = association<script, outpoint, tag, will>;
            using theory = vector<association>;
            
            theory brain;

            mind(theory b) : brain(b) {}

            thought what(script output, will outcome) const final override {
                for (association concept : brain) if (concept.Match(output)) {
                    //vector<tag> tags = concept.Tags(output);
                    
                    //std::vector<tag> have;
                    //for (tag t : tags) if (db.exists(t)) have.push_back(t);
                    
                    return concept.imagine(concept.Tags(output), outcome);
                }
                
                return nullptr;
            }
        };
        
        template <typename secret, typename script, typename outpoint, typename tag, typename will>
        struct single : public association<script, outpoint, tag, will> {
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
        struct multiple : public association<script, outpoint, tag, will> {
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
