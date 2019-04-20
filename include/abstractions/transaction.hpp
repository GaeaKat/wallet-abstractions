#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions {
        
    template <
        typename out,
        typename script, 
        typename txid,
        typename value, 
        typename transaction,
        typename script_pubkey
    > struct output : 
        public data::function::definition<transaction, out, txid>, 
        public data::function::definition<value, out, satoshi>, 
        public data::function::definition<script_pubkey, out, script> {};
        
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
