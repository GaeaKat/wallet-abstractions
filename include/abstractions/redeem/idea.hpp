#ifndef ABSTRACTIONS_REDEEM_IDEA_HPP
#define ABSTRACTIONS_REDEEM_IDEA_HPP

#include "redeemer.hpp"

namespace abstractions 
{
    namespace redeem
    {
        
        template <typename key, typename script, typename outpoint, typename out>
        using sighash = script (*const)(key, N, script, vertex<outpoint, out>, uint32_t);
        
        template <typename key, typename script, typename outpoint, typename out>
        using think = thought<script, outpoint, out> (*const)(key);
        
        template <typename key, typename script, typename outpoint, typename out>
        struct power : word<script, outpoint, out> {
            key Key;
            sighash<key, script, outpoint, out> Sighash;
            
            script speak(N value, script prev, vertex<outpoint, out> tx, uint32_t input_index) const final override {
                return Sighash(Key, value, prev, tx, input_index);
            };
            
            power(key k, sighash<key, script, outpoint, out> sh) : Key(k), Sighash(sh) {}
        };
    
    } // redeem
    
} // abstractions

#endif
