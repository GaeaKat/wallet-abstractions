// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_OUTPUT
#define ABSTRACTIONS_WALLET_OUTPUT

#include <abstractions/transaction.hpp>
#include <abstractions/script/script.hpp>
#include "script.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        using output = typename abstractions::output<script>::representation;
        
        struct op_return {
            const output* Output;
            
            op_return() : Output{} {}
            op_return(const output* const o) : Output{o} {}
            op_return(const op_return& o) : Output{o.Output} {}
            op_return(bytes data);
            
            static bool valid_old(const output& o);
            
            static bool valid(const output&);
        };

    }

}

#endif
