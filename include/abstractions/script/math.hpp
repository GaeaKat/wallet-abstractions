// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_SCRIPT_MATH
#define ABSTRACTIONS_SCRIPT_MATH

#include "functions.hpp"

namespace abstractions {
    
    namespace script {
        
        pointer<program> subtract(N);
        pointer<program> less256();
        pointer<program> greater256();
        pointer<program> less_equal256();
        pointer<program> greater_equal256();
        
        pointer<program> split256_to_32();
        
        inline pointer<program> subtract(N n) {
            return sequence({push(n), op(program::OP_SUB)});
        }
        
        inline pointer<program> split256_to_32() {
            return sequence({repeat(sequence({repeat(sequence({split(-4), to_alt_stack(), swap()}), 2)}), 7)});
        }
        
        inline pointer<program> less256() {
            return sequence({split256_to_32()});
        }
        
        inline pointer<program> greater256() {
            return sequence({split256_to_32()});
        }
        
        inline pointer<program> less_equal256() {
            return sequence({op(program::OP_SWAP), greater256()});
        }
        
        inline pointer<program> greater_equal256() {
            return sequence({op(program::OP_SWAP), less256()});
        }

    }

}

#endif
