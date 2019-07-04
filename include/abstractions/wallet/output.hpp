// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
            bool valid() {
                return output::valid() && output::ScriptPubKey.size() > 0 && ScriptPubKey[0] == abstractions::script::program::OP_RETURN;
            }
        };

    }

}

#endif
