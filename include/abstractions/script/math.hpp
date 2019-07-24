// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_MATH
#define ABSTRACTIONS_SCRIPT_MATH

#include "functions.hpp"

namespace abstractions {
    
    namespace script {
        
        pointer<program> subtract_32(N);
        
        pointer<program> less_32();
        pointer<program> greater_32();
        pointer<program> less_equal_32();
        pointer<program> greater_equal_32();
        
        pointer<program> less_32_verify();
        pointer<program> greater_32_verify();
        pointer<program> less_equal_32_verify();
        pointer<program> greater_equal_32_verify();
        
        pointer<program> less_256();
        pointer<program> greater_256();
        pointer<program> less_equal_256();
        pointer<program> greater_equal_256();
        
        pointer<program> less_256_verify();
        pointer<program> greater_256_verify();
        pointer<program> less_equal_256_verify();
        pointer<program> greater_equal_256_verify();
        
        inline pointer<program> subtract_32(N n) {
            return sequence({push(n), op(program::OP_SUB)});
        }
        
        inline pointer<program> less_32() {
            return op(program::OP_LESSTHAN);
        }
        
        inline pointer<program> greater_32() {
            return op(program::OP_GREATERTHAN);
        }
        
        inline pointer<program> less_equal_32() {
            return op(program::OP_LESSTHANOREQUAL);
        }
        
        inline pointer<program> greater_equal_32() {
            return op(program::OP_GREATERTHANOREQUAL);
        }
        
        inline pointer<program> less_32_verify() {
            return sequence({op(program::OP_LESSTHAN), op(program::OP_VERIFY)});
        }
        
        inline pointer<program> greater_32_verify() {
            return sequence({op(program::OP_GREATERTHAN), op(program::OP_VERIFY)});
        }
        
        inline pointer<program> less_equal_32_verify() {
            return sequence({op(program::OP_LESSTHANOREQUAL), op(program::OP_VERIFY)});
        }
        
        inline pointer<program> greater_equal_32_verify() {
            return sequence({op(program::OP_GREATERTHANOREQUAL), op(program::OP_VERIFY)});
        }
        
        inline pointer<program> less_equal_256() {
            return sequence({op(program::OP_SWAP), greater_256()});
        }
        
        inline pointer<program> greater_equal_256() {
            return sequence({op(program::OP_SWAP), less_256()});
        }
        
        inline pointer<program> less_equal_256_verify() {
            return sequence({op(program::OP_SWAP), greater_256()});
        }
        
        inline pointer<program> greater_equal_256_verify() {
            return sequence({op(program::OP_SWAP), less_256()});
        }

    }

}

#endif
