#ifndef ABSTRACTIONS_WALLET_OUTPUT
#define ABSTRACTIONS_WALLET_OUTPUT

#include <abstractions/transaction.hpp>
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using output = abstractions::output<script>;

    }

}

#endif
