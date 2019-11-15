// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_MATH
#define ABSTRACTIONS_SCRIPT_MATH

#include "functions.hpp"

namespace abstractions::script {
    
    program subtract(uint32);
    
    program less_verify();
    program greater_verify();
    program less_equal_verify();
    program greater_equal_verify();
    
    // Before the genesis upgrade, less and greater only work for 32-bit numbers. 
    // These functions enable big integer arithmetic for before this case. 
    program less_256();
    program greater_256();
    program less_equal_256();
    program greater_equal_256();
    
    program less_256_verify();
    program greater_256_verify();
    program less_equal_256_verify();
    program greater_equal_256_verify();
    
    inline program subtract(uint32 n) {
        return program{} + push(uint32_little{n}) + op_code(OP_SUB);
    }
    
    inline program less_verify() {
        return program{} + op_code(OP_LESSTHAN) + op_code(OP_VERIFY);
    }
    
    inline program greater_verify() {
        return program{} + op_code(OP_GREATERTHAN) + op(OP_VERIFY);
    }
    
    inline program less_equal_verify() {
        return program{} + op_code(OP_LESSTHANOREQUAL) + op_code(OP_VERIFY);
    }
    
    inline program greater_equal_verify() {
        return program{} + op_code(OP_GREATERTHANOREQUAL) + op_code(OP_VERIFY);
    }
    
    inline program less_equal_256() {
        return program{} + op_code(OP_SWAP), greater_256();
    }
    
    inline program greater_equal_256() {
        return program{} + op_code(OP_SWAP) + less_256();
    }
    
    inline program less_equal_256_verify() {
        return program{} + op_code(OP_SWAP) + greater_256_verify();
    }
    
    inline program greater_equal_256_verify() {
        return program{} + op_code(OP_SWAP) + less_256_verify();
    }

}

#endif
