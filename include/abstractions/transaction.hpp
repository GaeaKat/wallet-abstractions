// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    template <typename ops> 
    struct output : public std::vector<byte> {
        struct representation {
            bool Valid;
            satoshi Value;
            ops ScriptPubKey;
            
            representation(satoshi v, ops o) : Value{v}, ScriptPubKey{o} {}
            representation(&output);
        private:
            representation() : Valid{false}, Value{}, ScriptPubKey{} {}
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
    struct outpoint : public std::vector<byte> {
        struct representation {
            bool Valid;
            txid Reference;
            index Index;
            
            representation(txid tx, index i) : Valid{true}, Reference{tx}, Index{i} {}
            representation(outpoint&);
        private:
            representation() : Valid{false}, Reference{}, Index{} {}
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        txid reference() const;
        index index() const;
        
        outpoint();
        outpoint(bytes);
        outpoint(representation);
    };
    
    template <typename point, typename ops>
    struct input : public std::vector<byte> {
        struct representation {
            bool Valid;
            point Outpoint;
            ops ScriptSignature;
            N Sequence;
            
            representation(point p, ops s, N n) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
            representation(point p, ops s) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
            representation(input&);
        private:
            representation() : Valid{false}, Outpoint{}, ScriptSignature{}, Sequence{} {}
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
    };
    
    template <typename input, typename output>
    struct transaction : public std::vector<byte> {
        
        struct representation {
            bool Valid;
            N Locktime;
            list<input> Inputs;
            list<output> Outputs;
                
            representation(N l, list<input> i, list<output> o) :
                Valid{true}, Locktime{l}, Inputs{i}, Outputs{o} {}
            representation(transaction&);
        private:
            representation() : Valid{false}, Locktime{}, Inputs{}, Outputs{} {}
        };
        
        bool valid() const {
            return representation{*this}.Valid;
        }
        
        transaction();
        transaction(bytes);
        transaction(representation);
    };
    
} 

#endif
