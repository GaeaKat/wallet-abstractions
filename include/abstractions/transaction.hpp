// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <abstractions/timechain/transaction.hpp>
#include <abstractions/timechain/outpoint.hpp>
#include <abstractions/crypto/hash/sha512.hpp>

namespace abstractions {
    
    template <typename ops> 
    struct output : public std::vector<byte> {
        class representation {
            bool Valid;
        public:
            satoshi Value;
            ops ScriptPubKey;
            
            representation(satoshi v, ops o) : Valid{true}, Value{v}, ScriptPubKey{o} {}
            representation(const output&) noexcept;
            representation() : Valid{false}, Value{}, ScriptPubKey{} {}
            representation& operator=(const representation& o);
            
            ops script() const {
                return ScriptPubKey;
            }
            
            bool valid() const {
                return Valid;
            }
            
            satoshi value() const {
                return Value;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        satoshi value() const {
            return representation{*this}.Value;
        }
        
        const slice<byte> script() const;
        
        output() : std::vector<byte>{} {}
        output(bytes& b) : std::vector<byte>{b} {}
        output(const representation&) noexcept;
        
        output& operator=(const output& o) {
            std::vector<byte>::operator=(static_cast<bytes&>(o));
            return *this;
        }
        
        constexpr static timechain::output::interface<output<ops>::representation, ops> representation_is_output{};
    };
    
    template <typename txid>
    struct outpoint : public std::vector<byte> {
        using tx_index = abstractions::index;
        
        struct representation {
            bool Valid;
        public:
            txid Reference;
            tx_index Index;
            
            representation(txid tx, tx_index i) : Valid{true}, Reference{tx}, Index{i} {}
            representation(const outpoint&) noexcept;
            representation() : Valid{false}, Reference{}, Index{} {}
            representation& operator=(const representation& o);
            
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
        
        outpoint() : std::vector<byte>{} {}
        outpoint(bytes& b) : std::vector<byte>{b} {}
        outpoint(const representation&) noexcept;
        
        outpoint& operator=(const outpoint& o) {
            std::vector<byte>::operator=(static_cast<bytes&>(o));
            return *this;
        }
        
        constexpr static timechain::outpoint::interface<outpoint::representation, txid&, tx_index> is_outpoint{};
    };
    
    template <typename txid, typename ops>
    struct input : public std::vector<byte> {
        using point = typename outpoint<txid>::representation;
        
        struct representation {
            bool Valid;
        public:
            point Outpoint;
            ops ScriptSignature;
            uint32 Sequence;
            
            representation(point p, ops s, uint32 n) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
            representation(point p, ops s) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
            representation(const input&) noexcept;
            representation() : Valid{false}, Outpoint{}, ScriptSignature{}, Sequence{} {}
            representation& operator=(const representation& i);
            
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
        
        input() : std::vector<byte>{} {}
        input(bytes& b) : std::vector<byte>{b} {}
        input(const representation&) noexcept;
        
        input& operator=(const input& i) {
            std::vector<byte>::operator=(static_cast<bytes&>(i));
            return *this;
        }
    };
    
    template <typename in, typename out>
    struct transaction : public std::vector<byte> {
        
        struct representation {
            bool Valid;
        public:
            uint32 Version;
            uint32 Locktime;
            list<in> Inputs;
            list<out> Outputs;
                
            representation(uint32 l, list<in> i, list<out> o) :
                Valid{true}, Locktime{l}, Inputs{i}, Outputs{o} {}
                
            representation(list<in> i, list<out> o) :
                Valid{true}, Locktime{0}, Inputs{i}, Outputs{o} {}
                
            representation(const transaction&) noexcept;
            representation() : Valid{false}, Locktime{}, Inputs{}, Outputs{} {}
            representation& operator=(const representation& i);
            
            bool valid() const {
                return Valid;
            }
    
            slice<out> outputs() const {
                return Outputs;
            }
            
            slice<in> inputs() const {
                return Inputs;
            }
            
            uint32 locktime() const {
                return Locktime;
            }
            
            uint32 version() const {
                return Version;
            }
        
        };
        
        transaction() : std::vector<byte>{} {}
        transaction(bytes& b) : std::vector<byte>{b} {}
        transaction(const representation&) noexcept;
        transaction(N l, vector<in> i, vector<out> o) : transaction{representation{l, i, o}} {}
        transaction(vector<in> i, vector<out> o) : transaction{representation{i, o}} {}
        
        transaction& operator=(const transaction& t) {
            std::vector<byte>::operator=(static_cast<bytes&>(t));
            return *this;
        }
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        constexpr static timechain::transaction::interface<transaction::representation, in, out> is_tx{};
    };
    
} 

#endif
