// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM
#define ABSTRACTIONS_REDEEM

#include <abstractions/pattern.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    // A vertex is simply a transaction without input scripts. 
    // In other words, it represents a transaction that can
    // be signed to generate input scripts. 
    template <typename key, typename script, typename txid>
    struct vertex {
        using output = typename abstractions::output<script>::representation;
        using outpoint = typename abstractions::outpoint<txid>::representation;
        
        template <typename tx>
        using redeemer = typename pattern::abstract::redeemer<key, script, tx>&;
    
        struct spendable {
            key Key;
            output Output;
            outpoint Outpoint;
            
            bool valid() const {
                return Key.valid() && Output.valid() && Outpoint.valid();
            }
            
            spendable() : Key{}, Output{}, Outpoint{} {}
            spendable(key k, output o, outpoint p) : Key{k}, Output{o}, Outpoint{p} {}
            
            template <typename tx> 
            script redeem(redeemer<tx> r, tx t, index i) const {
                return r.redeem(Output.Value, Output.ScriptPubKey, t, i, Key);
            }
        };
    
        list<spendable> Inputs;
        list<output> Outputs;
        
        vertex(list<spendable> i, list<output> o) : Inputs{i}, Outputs{o} {}
        
        uint expected_size() const;
        
        bytes write() const;
        
    };
    
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx>
    tx redeem(list<pattern::abstract::recognizable<key, script, tag, tx>&> patterns, vertex<key, out, point> v) noexcept;
    
}

#endif
