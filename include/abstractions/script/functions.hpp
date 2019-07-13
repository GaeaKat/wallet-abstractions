// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_FUNCTIONS
#define ABSTRACTIONS_SCRIPT_FUNCTIONS

#include "script.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>

namespace abstractions {
    
    namespace script {
        pointer<program> op(program::op);
        pointer<program> sequence(std::vector<pointer<program>>);
        pointer<program> push(bytes);
        pointer<program> push(bitcoin::signature);
        pointer<program> push(bitcoin::pubkey);
        pointer<program> push(bitcoin::address);
        pointer<program> push(N);
        pointer<program> noop();
        pointer<program> repeat(pointer<program>, N);
        pointer<program> dup();
        pointer<program> swap();
        pointer<program> to_alt_stack();
        pointer<program> from_alt_stack();
        pointer<program> concat();
        pointer<program> concat(N);
        pointer<program> rotate_bytes(Z);
        pointer<program> rotate_bytes_left(N);
        pointer<program> rotate_bytes_right(N);
        pointer<program> rotate_bytes_left();
        pointer<program> rotate_bytes_right();
        pointer<program> split(N);
        pointer<program> equal();
        pointer<program> bitcoin_hash();
        pointer<program> address_hash();
        pointer<program> sha256_hash();
        pointer<program> check_signature(); 
        
        inline pointer<program> op(program::op o) {
            return std::make_shared<program>(new program::op_code{o});
        }
        
        inline pointer<program> sequence(std::vector<pointer<program>> v) {
            return std::make_shared<program>(new program::sequence{v});
        }
        
        inline pointer<program> push(bytes b) {
            return std::make_shared<program>(new program::push{b});
        }
        
        inline pointer<program> repeat(pointer<program> p, N n) {
            return std::make_shared<program>(new program::repeated{n, p});
        }
        
        inline pointer<program> dup() {
            return op(program::OP_DUP);
        }
        
        inline pointer<program> to_alt_stack() {
            return op(program::OP_TOALTSTACK);
        }
        
        inline pointer<program> from_alt_stack() {
            return op(program::OP_FROMALTSTACK);
        }
        
        inline pointer<program> concat() {
            return op(program::OP_CAT);
        }
        
        inline pointer<program> concat(N n) {
            return repeat(concat(), n);
        }
        
        inline pointer<program> rotate_bytes(Z z) {
            if (z == 0) return noop();
            if (z < 0) return rotate_bytes_left(-z);
            return rotate_bytes_right(z);
        }
        
        inline pointer<program> split(N n) {
            return sequence({push(n), op(program::OP_SPLIT)});
        }
        
        inline pointer<program> equal() {
            return op(program::OP_EQUAL);
        }
        
        inline pointer<program> bitcoin_hash() {
            return op(program::OP_HASH256);
        }
        
        inline pointer<program> address_hash() {
            return op(program::OP_HASH160);
        }
        
        inline pointer<program> check_signature() {
            return op(program::OP_CHECKSIG);
        }
        
    }
    
}

#endif

