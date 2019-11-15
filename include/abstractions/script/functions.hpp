// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_FUNCTIONS
#define ABSTRACTIONS_SCRIPT_FUNCTIONS

#include "script.hpp"
#include "push.hpp"
#include "instructions.hpp"
#include <data/fold.hpp>

namespace abstractions::script {
    program repeat(program, uint32);
    program concat(uint32);
    program rotate_bytes_left(uint32);
    program split(uint32);
    
    inline program repeat(program p, uint32 n) {
        return data::nest([p](program x)->program{return x + p;}, program{}, n);
    }
    
    inline program concat(uint32 n) {
        return repeat(program{} + cat(), n - 1);
    }
    
    inline program rotate_bytes_left(uint32 n) {
        return program{} + split(n) + cat();
    }
    
    inline program split(uint32 n) {
        return program{} + push(uint32_little{n}) + op_code(OP_SPLIT);
    }
    
}

#endif

