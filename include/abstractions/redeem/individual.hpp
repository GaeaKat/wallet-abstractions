#ifndef ABSTRACTIONS_REDEEM_INDIVIDUAL_HPP
#define ABSTRACTIONS_REDEEM_INDIVIDUAL_HPP

#include <abstractions/database.hpp>

#include <abstractions/redeem/mind.hpp>

#include <abstractions/redeem/could.hpp>

namespace abstractions 
{
    
    namespace redeem
    {
        
        template <typename key, typename script, typename outpoint, typename out>
        using sign = script (*const)(key, N, script, vertex<outpoint, out>, uint32_t);
        
        template <typename key, typename script, typename outpoint, typename out>
        struct logos : word<script, outpoint, out> {
            const key Key; 
            sign<key, script, outpoint, out> Sign;
            
            script speak(N value, script prevout, vertex<outpoint, out> x, uint32_t input_index) const final override {
                return Sign(Key, value, prevout, x, input_index);
            };
            
            logos(key k, sign<key, script, outpoint, out> s) : Key(k), Sign(s) {}
        };
        
        template <typename key, typename script, typename outpoint, typename out, typename tag>
        struct individual : association<script, outpoint, out, tag, accomplishment> {
            const database<tag, key>& Database;
            sign<key, script, outpoint, out> Sign;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint, out> imagine(vector<tag> addrs, accomplishment w) const {
                if (w != redeemed) return nullptr;
                if (addrs.size() != 1) return nullptr;
                
                entry<key> e = Database.get(addrs[0]);
                if (!e.Exists) return nullptr;
                
                return std::shared_ptr<word<script, outpoint, out>>(new logos<S, P, script, outpoint, output>(e.Value, Sign));
            };
            
            individual(
                pattern<script> match,
                tags<tag, script> tags,
                const database<tag, key>& d, 
                sign<key, script, outpoint, out> s)
                : association<script, outpoint, out, tag, accomplishment>(match, tags), Database(d), Sign(s) {}
        };
    }
}

#endif
