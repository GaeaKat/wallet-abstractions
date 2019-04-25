// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions {
    
    template <typename script> 
    struct output {
        satoshi Value;
        script ScriptPubKey;
        
        output(satoshi v, script s) : Value{v}, ScriptPubKey{s} {}
    };
    
    template <typename txid>
    struct outpoint {
        txid Transaction;
        index Index;
        
        outpoint(txid tx, index i) : Transaction{tx}, Index{i} {}
    };
    
    template <typename point, typename script>
    struct input {
        point Outpoint;
        script ScriptSignature;
        N Sequence;
        
        input(point p, script s, N n) : Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
        input(point p, script s) : Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
    };
    
    template <
        typename tx,
        typename txid, 
        typename in, 
        typename out,
        typename id, 
        typename inputs,
        typename outputs
    > struct transaction : 
        public data::function::definition<id, tx, txid>, 
        public data::function::definition<inputs, tx, slice<in>>, 
        public data::function::definition<outputs, tx, slice<out>> {};
    
} 

#endif
