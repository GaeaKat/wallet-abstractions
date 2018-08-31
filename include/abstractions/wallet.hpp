#ifndef ABSTRACTIONS_WALLET_HPP
#define ABSTRACTIONS_WALLET_HPP

#include "output.hpp"
#include "set.hpp"
#include "link.hpp"

namespace abstractions
{
    template <typename point, typename key, typename out, typename script, typename tag>
    struct wallet {
        output::value<out> GetValue;
        output::script<out, script> GetScript;
        
        map<point, out> Outpoints;
        
        map<pattern<script>, tags<tag, script>> Patterns;
        
        vector<one_way<key, tag>> Tags;
        
        const set<key> Keys;
        
        bool valid() {
            if (GetValue == nullptr || GetScript == nullptr) return false;
            
            std::map<tag, point> tags;
            set<point> outpoints{};
            
            // Check that every output matches a pattern. 
            for(point p : Outpoints) {
                for(pattern<script> match : Patterns) if (match(Outpoints[p])) {
                    for (tag t : Patterns[match](Outpoints[p])) tags.insert(std::make_pair(t, p));
                    outpoints += p;
                    continue;
                }
                return false;
            }
            
            // check that for every output a key and tag function
            // exist such that the generated tags is among
            // those which can be extracted from the output. 
            for (set<key> keys = Keys; keys != nullptr; keys = keys->Next) {
                for (one_way<key, tag> f : Tags) {
                    auto x = tags.find(f(keys->First));
                    if (x != tags.end()) outpoints -= *x;
                }
                return false;
            }
            
            return outpoints == nullptr;
        }
        
        wallet(
            output::value<out> gv, 
            output::script<out, script> gs,
            map<point, out> pt,
            map<pattern<script>, tags<tag, script>> p, 
            vector<one_way<key, tag>> t,
            set<key> k) : GetValue(gv), GetScript(gs), Outpoints(p), Patterns(p), Tags(t), Keys(k) {}
    };
    
    template <typename point, typename key, typename out>
    N balance(output::value<out> v, set<out> wallet) {
        if (wallet == nullptr) return 0;
        return v(wallet->First) + balance(v, wallet->Rest);
    }
}

#endif
