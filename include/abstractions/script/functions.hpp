// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
        pointer<program> repeat(pointer<program>, N);
        pointer<program> dup();
        pointer<program> to_alt_stack();
        pointer<program> from_alt_stack();
        pointer<program> concat();
        pointer<program> concat(N);
        pointer<program> rotate_bits(Z);
        pointer<program> split(Z);
        pointer<program> bitcoin_hash();
        pointer<program> less();
        pointer<program> greater();
        pointer<program> less_equal();
        pointer<program> greater_equal();
        pointer<program> pay_to_address(bitcoin::address);
        pointer<program> redeem_from_pay_to_address(bitcoin::pubkey, bitcoin::signature);
        
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
        
    }
    
}

#endif

