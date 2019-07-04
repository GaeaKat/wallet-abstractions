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
        
        
        inline pointer<program> less_equal256() {
            return sequence({op(program::OP_SWAP), greater256()});
        }
        
        inline pointer<program> greater_equal256() {
            return sequence({op(program::OP_SWAP), less256()});
        }

    }

}
