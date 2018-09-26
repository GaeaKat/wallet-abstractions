#ifndef ABSTRACTIONS_LINK_HPP
#define ABSTRACTIONS_LINK_HPP

#include "observe.hpp"
#include "one_way.hpp"

namespace abstractions
{

    template<typename key, typename script, typename tag> 
    struct concept {
        pattern<script> Match;
            
        // What tags are associated with this pattern? 
        tags<script, tag> GetTags;
        
        one_way<key, tag> Tag;
        
        bool verify(key k, script s) const {
            if (!Match(s)) return false;
            
            tag ad = Tag(k);
            for (tag t : GetTags(s)) if (t == ad) return true;
            
            return false;
        }
    };

    template<typename key, typename script, typename tag> 
    struct link {
        script ScriptPubKey;
        
        concept<key, script, tag> Concept;
    };
    
    template <typename key, typename out, typename script, typename tag>
    knowledge is_mine(key k, link<key, script, tag> l) {
        l.Concept.verify(k, l.ScriptPubKey);
    }

}

#endif

