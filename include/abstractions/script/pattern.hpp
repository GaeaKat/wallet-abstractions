// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PATTERN
#define ABSTRACTIONS_SCRIPT_PATTERN

#include "script.hpp"

namespace abstractions::script {
    class pattern {
        // an element is either an instruction or a pattern
        // that matches any pushdata and which is set to
        // any data that might be there. 
        struct element {
            instruction Instruction;
            bool Push;
            bytes * Variable;
        
            element(instruction i) : Instruction{i}, Push{false}, Variable{nullptr} {}
            element(bytes& b) : Instruction{}, Push{true}, Variable{&b} {}
            element() : Instruction{}, Push{true}, Variable{nullptr} {}
            
            bool valid() {
                return Push || Instruction.valid();
            }
            
            bool set(const bytes& b) {
                if (!Push) return false;
                if (Variable != nullptr) *Variable = b;
                return true;
            }
        
            bool match(instruction i) {
                if (Push) {
                    if (!is_push(i.Op)) return false;
                    return set(i.data());
                }
                
                return Instruction == i;
            }
        };
        
        queue<element> Elements;
        pattern(queue<element> e) : Elements{e} {}
        
        static bool match(queue<element> e, program p);
        
    public:
        pattern() : Elements{} {}
        
        pattern operator+(instruction i) const {
            return pattern{Elements + element{i}};
        }
        
        pattern operator+(bytes& b) const {
            return pattern{Elements + element{b}};
        }
        
        bool match(program p) const {
            return match(Elements, p);
        }
    };
    
}

#endif
