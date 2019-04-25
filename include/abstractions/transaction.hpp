// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions {
        
    template <typename script> struct output {
        satoshi Value;
        script ScriptPubKey;
        
        output(satoshi v, script s) : Value{v}, ScriptPubKey{s} {}
    };
        
    template <
        typename point,
        typename txid,
        typename transaction,
        typename output_index
    > struct outpoint : 
        public data::function::definition<transaction, point, txid>, 
        public data::function::definition<output_index, point, index> {};
        
    template <
        typename in,
        typename script,
        typename point,
        typename output_point, 
        typename script_sig
    > struct input : 
        public data::function::definition<output_point, in, point>, 
        public data::function::definition<script_sig, in, script> {};
        
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
