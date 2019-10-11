// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <abstractions/timechain/transaction.hpp>
#include <abstractions/timechain/outpoint.hpp>
#include <abstractions/value.hpp>
#include <abstractions/crypto/address.hpp>

namespace abstractions {
    
    template <typename txid>
    struct outpoint {
        using tx_index = abstractions::index;
        txid Reference;
        tx_index Index;
        
        outpoint(txid tx, index i) : Reference{tx}, Index{i} {}
        outpoint() : Reference{}, Index{0} {}
        
        bool valid() const {
            return data::valid(Reference);
        }
        
        const txid& reference() const {
            return Reference;
        }
        
        tx_index index() const {
            return Index;
        }
        
        size_t size() const {
            return 36;
        }
        
        bytes serialize() const {
            return timechain::outpoint::serialize(*this);
        }
        
        explicit operator bytes() const {
            return serialize();
        }
        
        constexpr static timechain::outpoint::interface<outpoint, const txid&, tx_index> is_outpoint{};
    };
    
    template <typename txid, typename ops>
    struct input {
        using point = outpoint<txid>;
        
        point Outpoint;
        ops ScriptSignature;
        uint32 Sequence;
        
        input(point p, ops s, uint32 n) : Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
        input(point p, ops s) : Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
        input() : Outpoint{}, ScriptSignature{}, Sequence{} {}
        
        bool valid() const {
            return data::valid(Outpoint) && data::valid(ScriptSignature);
        }
        
        point previous() const {
            return Outpoint;
        }
        
        const ops& script() const {
            return ScriptSignature;
        }
            
        uint32 sequence() const {
            return Sequence;
        }
        
        size_t size() const {
            return 40 + timechain::size_with_var_int_prefix(ScriptSignature);
        }
        
        bytes serialize() const {
            return timechain::input::serialize(*this);
        }
        
        explicit operator bytes() const {
            return serialize();
        }
        
        constexpr static timechain::input::interface<input, point, const ops&, uint32> is_input{};
    };
    
    template <typename ops> 
    struct output {
        satoshi Value;
        ops ScriptPubKey;
        
        output(satoshi v, ops o) : Value{v}, ScriptPubKey{o} {}
        output() : Value{}, ScriptPubKey{} {}
        
        bool valid() const {
            return data::valid(ScriptPubKey);
        }
        
        satoshi value() const {
            return Value;
        }
        
        const ops& script() const {
            return ScriptPubKey;
        }
        
        size_t size() const {
            return 8 + timechain::size_with_var_int_prefix(ScriptPubKey);
        }
        
        bytes serialize() const {
            return timechain::output::serialize(*this);
        }
        
        explicit operator bytes() const {
            return serialize();
        }
        
        constexpr static timechain::output::interface<output<ops>, satoshi, const ops&> is_output{};
    };
    
    template <typename in, typename out>
    struct vertex {
        queue<in> Inputs;
        queue<out> Outputs;
        
        vertex() : Inputs{}, Outputs{} {}
        vertex(queue<in> i, queue<out> o) : Inputs{i}, Outputs{o} {}
        
        satoshi spent() const {
            return reduce([](satoshi v, out x)->satoshi{
                return value(x) + v;
            }, Outputs);
        }
        
        bool valid() const {
            return data::valid(Inputs) && data::valid(Outputs) && Inputs.size() > 0 && Outputs.size() > 0;
        }
        
        queue<in> inputs() const {
            return Inputs;
        }
        
        queue<out> outputs() const {
            return Outputs;
        }
    };
    
    template <typename txid, typename ops>
    struct transaction : public abstractions::vertex<input<txid, ops>, output<ops>> {
        using in = input<txid, ops>;
        using out = output<ops>;
        using vertex = abstractions::vertex<in, out>;
        int32 Version;
        uint32 Locktime;
            
        transaction(int32 v, queue<in> i, queue<out> o, uint32 l) : vertex{i, o}, 
            Version{v}, Locktime{l} {}
        
        transaction(int32 v, queue<in> i, queue<out> o) : transaction{v, i, o, 0} {}
        transaction(queue<in> i, queue<out> o,uint32 l) : transaction{2, i, o, l} {}
        transaction(queue<in> i, queue<out> o) : transaction{2, i, o} {}
            
        transaction() : vertex{}, Version{-1}, Locktime{0} {}
        
        bool valid() const {
            return vertex::valid();
        }
        
        uint32 locktime() const {
            return Locktime;
        }
        
        int32 version() const {
            return Version;
        }
        
        size_t size() const {
            return 8 + timechain::size_with_var_int_prefix(vertex::Inputs) + 
                timechain::size_with_var_int_prefix(vertex::Outputs) + 
                reduce(data::plus<size_t>{}, for_each(timechain::size_with_var_int_prefix<in>, vertex::Inputs)) + 
                reduce(data::plus<size_t>{}, for_each(timechain::size_with_var_int_prefix<out>, vertex::Outputs));
        }
        
        txid id() const {
            return crypto::txid(serialize());
        }
        
        bytes serialize() const {
            return timechain::transaction::serialize(*this);
        }
        
        explicit operator bytes() const {
            return serialize();
        }
        
        constexpr static timechain::transaction::interface<transaction, int32, in, out, uint32, txid> is_tx{};
    };
    
} 

#endif
