// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/math.hpp>
#include <abstractions/script/instructions.hpp>

namespace abstractions::script {
        
    program get_words_32() {
        return program{} + split(4) + swap() + to_alt() + swap() + split(4) + swap() + to_alt();
    }
        
    program less_256() {
        return repeat(program{} + get_words_32() + less() + from_alt() + from_alt(), 7) + 
            less() + 
            repeat(program{} + op_code(OP_AND), 7);
    }
    
    program greater_256() {
        return repeat(program{} + get_words_32() + greater() + from_alt() + from_alt(), 7) + 
            greater() + 
            repeat(program{} + op_code(OP_AND), 7);
    }
    
    program less_256_verify() {
        return repeat(program{} + get_words_32() + less_verify() + from_alt() + from_alt(), 7) + 
            less_verify();
    }
    
    program greater_256_verify() {
        return repeat(program{} + get_words_32() + greater_verify() + from_alt() + from_alt(), 7) +  
            greater_verify();
    }

}
