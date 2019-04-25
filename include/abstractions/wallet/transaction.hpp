// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_TRANSACTION
#define ABSTRACTIONS_WALLET_TRANSACTION

#include <abstractions/fundamental.hpp>
#include <abstractions/data.hpp>
#include "input.hpp"
#include "output.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct transaction : public std::vector<byte> {
            transaction();
            transaction(bytes);
            transaction(list<bitcoin::input>, list<output>);
            
            N locktime() const;
            list<bitcoin::input> inputs();
            list<output> outputs();
        };
        
    }

}

#endif
