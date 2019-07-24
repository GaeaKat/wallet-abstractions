// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/math.hpp>

namespace abstractions::script {
        
    pointer<program> get_words_32() {
        return sequence({
            split(4), 
            swap(), 
            to_alt(), 
            swap(), 
            split(4),
            swap(), 
            to_alt()
        });
    }
        
    pointer<program> less_256() {
        return sequence({
            repeat(sequence({get_words_32(), less_32(), from_alt(), from_alt()}), 7), 
            less_32(),
            repeat(sequence({op(program::OP_AND)}), 7)
        });
    }
    
    pointer<program> greater_256() {
        return sequence({
            repeat(sequence({get_words_32(), greater_32(), from_alt(), from_alt()}), 7), 
            greater_32(),
            repeat(sequence({op(program::OP_AND)}), 7)
        });
    }
    
    pointer<program> less_256_verify() {
        return sequence({
            repeat(sequence({get_words_32(), less_32_verify(), from_alt(), from_alt()}), 7), 
            less_32_verify()
        });
    }
    
    pointer<program> greater_256_verify() {
        return sequence({
            repeat(sequence({get_words_32(), greater_32_verify(), from_alt(), from_alt()}), 7), 
            greater_32_verify()
        });
    }

}
