// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <abstractions/timechain/transaction.hpp>
#include <abstractions/crypto/hash/sha512.hpp>

namespace abstractions {
    
    template <typename ops> 
    struct output : public bytes {
        class representation {
            bool Valid;
        public:
            satoshi Value;
            ops ScriptPubKey;
            
            representation(satoshi v, ops o) : Valid{true}, Value{v}, ScriptPubKey{o} {}
            representation(output);
            representation() : Valid{false}, Value{}, ScriptPubKey{} {}
            
            ops script() const {
                return ScriptPubKey;
            }
            
            bool valid() const {
                return Valid;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        satoshi value() const;
        slice<byte>& script() const;
        
        output();
        output(bytes);
        output(representation);
        
        constexpr static timechain::output::interface<output::representation, ops> representation_is_output{};
        constexpr static timechain::output::interface<output, slice<byte>&> is_output{};
    };
    
    template <typename txid>
    struct outpoint : public bytes {
        using tx_index = abstractions::index;
        
        struct representation {
            bool Valid;
        public:
            txid Reference;
            tx_index Index;
            
            representation(txid tx, tx_index i) : Valid{true}, Reference{tx}, Index{i} {}
            representation(outpoint);
            representation() : Valid{false}, Reference{}, Index{} {}
            
            bool valid() const {
                return Valid;
            }
            
            txid& reference() const {
                return Reference;
            }
            
            tx_index index() const {
                return Index;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        txid& reference() const;
        tx_index index() const;
        
        outpoint();
        outpoint(bytes);
        outpoint(representation);
        
        outpoint& operator=(outpoint);
    };
    
    template <typename txid, typename ops>
    struct input : public bytes {
        using point = typename outpoint<txid>::representation;
        
        struct representation {
            bool Valid;
        public:
            point Outpoint;
            ops ScriptSignature;
            uint32 Sequence;
            
            representation(point p, ops s, N n) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
            representation(point p, ops s) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
            representation(input);
            representation() : Valid{false}, Outpoint{}, ScriptSignature{}, Sequence{} {}
            
            ops& script() const {
                return ScriptSignature;
            }
            
            bool valid() const {
                return Valid;
            }
            
            uint32 sequence() const {
                return Sequence;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        slice<byte> script() const;
        uint32 sequence() const;
        outpoint<txid>& outpoint() const;
        
        input();
        input(bytes);
        input(representation);
        
        input& operator=(input);
    };
    
    template <typename txid, typename ops>
    struct transaction : public bytes {
        
        using in = typename input<txid, ops>::representation;
        using out = typename output<ops>::representation;
        
        struct representation {
            bool Valid;
        public:
            uint32 Locktime;
            list<in> Inputs;
            list<out> Outputs;
                
            representation(uint32 l, list<in> i, list<out> o) :
                Valid{true}, Locktime{l}, Inputs{i}, Outputs{o} {}
                
            representation(list<in> i, list<out> o) :
                Valid{true}, Locktime{0}, Inputs{i}, Outputs{o} {}
                
            representation(transaction);
            representation() : Valid{false}, Locktime{}, Inputs{}, Outputs{} {}
            
            bool valid() const {
                return Valid;
            }
    
            slice<out> outputs() const {
                return Outputs;
            }
            
            slice<in> inputs() const {
                return Inputs;
            }
            
            txid hash() const {
                return transaction{*this}.hash();
            }
            
            uint32 locktime() const {
                return Locktime;
            }
        
        };
        
        transaction();
        transaction(bytes);
        transaction(representation);
        transaction(N l, vector<in> i, vector<out> o) : transaction{representation{l, i, o}} {}
        transaction(vector<in> i, vector<out> o) : transaction{representation{i, o}} {}
        
        transaction& operator=(transaction);
        
        bool valid() const {
            return representation{*this}.Valid;
        }
            
        sha512::digest hash() const {
            return sha512::hash(static_cast<bytes&>(*this));
        }
    
        slice<output<ops>> outputs() const;
        slice<input<txid, ops>> inputs() const;
        uint32 locktime() const;
        
        //constexpr static timechain::transaction::interface<transaction::representation, in, out, txid> representation_is_tx{};
        constexpr static timechain::transaction::interface<transaction, input<txid, ops>, output<ops>, txid> is_tx{};
    };
    
} 

#endif
