#ifndef ABSTRACTIONS_WALLET_INPUT
#define ABSTRACTIONS_WALLET_INPUT

#include "outpoint.hpp"
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct input {
            outpoint Outpoint;
            script ScriptSignature;
        };
        
    }
    
} 

#endif
