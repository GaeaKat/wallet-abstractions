// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM
#define ABSTRACTIONS_REDEEM

#include <abstractions/pattern.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    
    // vertex is used to construct Bitcoin transactions.     
    template <typename key, typename script, typename txid>
    struct vertex {
        using output = typename abstractions::output<script>::representation;
        using outpoint = typename abstractions::outpoint<txid>::representation;
        using input = typename input<txid, script>::representation;
        using tx = transaction<input, output>;
        using redeemer = const typename pattern::abstract::redeemer<key, script, tx>&;
    
        struct spendable {
            key Key;
            output Output;
            outpoint Outpoint;
            redeemer Redeemer;
            
            bool valid() const {
                return Key.valid() && Output.valid() && Outpoint.valid();
            }
            
            spendable(key k, output o, outpoint p, redeemer r) : Key{k}, Output{o}, Outpoint{p}, Redeemer{r} {}
            
            input redeem(tx t, index i) const {
                return input{Outpoint, Redeemer.redeem(Output.value(), Output.script(), t, i, Key)};
            }
        };
    
        vector<spendable> Inputs;
        vector<output> Outputs;
        
        vertex(vector<spendable> i, vector<output> o) : Inputs{i}, Outputs{o} {}
        
        uint expected_size() const;
        satoshi redeemed() const;
        satoshi spent() const ;
        
        satoshi fee() const {
            return [](satoshi r, satoshi s)->satoshi{if (s > r) return 0; return r - s;}(redeemed(), spent());
        }
        
        tx redeem() const;
    private:
        tx write() const;
    };
    
}

#endif
