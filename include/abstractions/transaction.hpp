// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TRANSACTION
#define ABSTRACTIONS_TRANSACTION

#include <data/function.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    template <typename script> 
    struct output : public std::vector<byte> {
        struct representation {
            bool Valid;
            satoshi Value;
            script ScriptPubKey;
            
            representation(satoshi v, script s) : Value{v}, ScriptPubKey{s} {}
            representation(output);
        private:
            representation() : Valid{false}, Value{}, ScriptPubKey{} {}
        };
        
        bool valid() const;
        
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
            representation(outpoint);
        private:
            representation() : Valid{false}, Reference{}, Index{} {}
        };
        
        bool valid() const;
        
        outpoint();
        outpoint(bytes);
        outpoint(representation);
    };
    
    template <typename point, typename script>
    struct input : public std::vector<byte> {
        struct representation {
            bool Valid;
            point Outpoint;
            script ScriptSignature;
            N Sequence;
            
            representation(point p, script s, N n) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{n} {}
            representation(point p, script s) : Valid{true}, Outpoint{p}, ScriptSignature{s}, Sequence{0} {}
            representation(input);
        private:
            representation() : Valid{false}, Outpoint{}, ScriptSignature{}, Sequence{} {}
        };
        
        bool valid() const;
        
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
            representation(transaction);
        private:
            representation() : Valid{false}, Locktime{}, Inputs{}, Outputs{} {}
        };
        
        bool valid() const;
        
        transaction();
        transaction(bytes);
        transaction(representation);
    };
    
} 

#endif
