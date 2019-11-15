// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_INSTRUCTIONS
#define ABSTRACTIONS_SCRIPT_INSTRUCTIONS

#include "script.hpp"

namespace abstractions::script {
    instruction dup();
    instruction swap();
    instruction to_alt();
    instruction from_alt();
    instruction equal();
    instruction verify();
    instruction equal_verify();
    instruction bitcoin_hash();
    instruction address_hash();
    instruction sha256_hash();
    instruction check_signature(); 
        
    instruction less();
    instruction greater();
    instruction less_equal();
    instruction greater_equal();
    
    inline instruction dup() {
        return op_code(OP_DUP);
    }
    
    inline instruction swap() {
        return op_code(OP_SWAP);
    }
    
    inline instruction to_alt() {
        return op_code(OP_TOALTSTACK);
    }
    
    inline instruction from_alt() {
        return op_code(OP_FROMALTSTACK);
    }
    
    inline instruction cat() {
        return op_code(OP_CAT);
    }
    
    inline instruction equal() {
        return op_code(OP_EQUAL);
    }
    
    inline instruction verify() {
        return op_code(OP_VERIFY);
    }
    
    inline instruction equal_verify() {
        return op_code(OP_EQUALVERIFY);
    }
    
    inline instruction bitcoin_hash() {
        return op_code(OP_HASH256);
    }
    
    inline instruction address_hash() {
        return op_code(OP_HASH160);
    }
    
    inline instruction check_signature() {
        return op_code(OP_CHECKSIG);
    }
    
    inline instruction less() {
        return op_code(OP_LESSTHAN);
    }
    
    inline instruction greater() {
        return op_code(OP_GREATERTHAN);
    }
    
    inline instruction less_equal() {
        return op_code(OP_LESSTHANOREQUAL);
    }
    
    inline instruction greater_equal() {
        return op_code(OP_GREATERTHANOREQUAL);
    }
}

#endif
