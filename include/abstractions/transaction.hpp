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
            int32 Version;
            list<in> Inputs;
            list<out> Outputs;
            uint32 Locktime;
                
            representation(int32 v, list<in> i, list<out> o,uint32 l) :
                Valid{true}, Version{v}, Inputs{i}, Outputs{o}, Locktime{l} {}
                
            representation(int32 v, list<in> i, list<out> o) : representation{v, i, o, 0} {}
            representation(list<in> i, list<out> o,uint32 l) : representation{2, i, o, l} {}
            representation(list<in> i, list<out> o) : representation{2, i, o} {}
            
            representation(const transaction&) noexcept;
            representation() : Valid{false}, Inputs{}, Outputs{}, Locktime{} {}
            
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
            
            int32 version() const {
                return Version;
            }
            
            satoshi fee() const;
        
        };
        
        transaction() : std::vector<byte>{} {}
        transaction(bytes& b) : std::vector<byte>{b} {}
        transaction(const representation&) noexcept;
        transaction(vector<in> i, vector<out> o) : transaction{representation{i, o}} {}
        transaction(vector<in> i, vector<out> o, uint32 l) : transaction{representation{i, o, l}} {}
        
        transaction& operator=(const transaction& t) {
            std::vector<byte>::operator=(static_cast<bytes&>(t));
            return *this;
        }
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        uint32 locktime() const {
            return representation{*this}.Locktime;
        }
        
        int32 version() const {
            return representation{*this}.Version;
        }
        
        satoshi fee() const {
            return representation{*this}.fee();
        }
        
        slice<bytes> outputs() const;
        slice<bytes> inputs() const;
        
        constexpr static timechain::transaction::interface<transaction::representation, in, out> representation_is_tx{};
        constexpr static timechain::transaction::interface<transaction, bytes, bytes> is_tx{};
    };
    
} 

#endif
