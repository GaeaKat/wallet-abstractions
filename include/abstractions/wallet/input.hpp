#ifndef ABSTRACTIONS_WALLET_INPUT
#define ABSTRACTIONS_WALLET_INPUT

#include "script.hpp"
#include "outpoint.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct input {
            outpoint Outpoint;
            script ScriptSignature;
        };
        
    }
    
} 

#endif
