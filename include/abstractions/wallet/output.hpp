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
        
        struct op_return : public output {
            op_return() : output{} {}
            op_return(output o) : output{o} {}
            op_return(op_return& o) : output{static_cast<output&>(o)} {}
            op_return(bytes data);
            bool valid() const {
                return output::valid() && output::ScriptPubKey.size() > 0 && ScriptPubKey[0] == abstractions::script::program::OP_RETURN;
            }
        };

    }

}

#endif
