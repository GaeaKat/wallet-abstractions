// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>

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
        ops script() const;
        
        output();
        output(bytes);
        output(representation);
    };
    
    template <typename txid>
    struct outpoint : public bytes {
        struct representation {
            bool Valid;
        public:
            txid Reference;
            index Index;
            
            representation(txid tx, index i) : Valid{true}, Reference{tx}, Index{i} {}
            representation(outpoint);
            representation() : Valid{false}, Reference{}, Index{} {}
            
            bool valid() const {
                return Valid;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        txid reference() const;
        index index() const;
        
        outpoint();
        outpoint(bytes);
        outpoint(representation);
        
        outpoint& operator=(outpoint);
    };
    
    template <typename point, typename ops>
    struct input : public bytes {
        struct representation {
            bool Valid;
        public:
            point Outpoint;
            ops ScriptSignature;
            N Sequence;
            
            representation(point p, ops s, N n) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
            representation(point p, ops s) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
            representation(input);
            representation() : Valid{false}, Outpoint{}, ScriptSignature{}, Sequence{} {}
            
            ops script() const {
                return ScriptSignature;
            }
            
            bool valid() const {
                return Valid;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        ops script() const;
        N sequence() const;
        point outpoint() const;
        
        input();
        input(bytes);
        input(representation);
        
        input& operator=(input);
    };
    
    template <typename input, typename output>
    struct transaction : public bytes {
        
        struct representation {
            bool Valid;
        public:
            N Locktime;
            list<input> Inputs;
            list<output> Outputs;
                
            representation(N l, list<input> i, list<output> o) :
                Valid{true}, Locktime{l}, Inputs{i}, Outputs{o} {}
                
            representation(list<input> i, list<output> o) :
                Valid{true}, Locktime{0}, Inputs{i}, Outputs{o} {}
                
            representation(transaction);
            representation() : Valid{false}, Locktime{}, Inputs{}, Outputs{} {}
            
            bool valid() const {
                return Valid;
            }
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        transaction();
        transaction(bytes);
        transaction(representation);
        transaction(N l, list<input> i, list<output> o) : transaction{representation{l, i, o}} {}
        transaction(list<input> i, list<output> o) : transaction{representation{i, o}} {}
        
        transaction& operator=(transaction);
    };
    
} 

#endif
