// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_MACHINE
#define ABSTRACTIONS_WALLET_MACHINE

#include <abstractions/machine.hpp>
#include <abstractions/wallet/transaction.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct machine {
            // Run machine without checking signatures. 
            machine();
            
            // Run the machine with checking signatures. 
            machine(transaction& tx, index i, satoshi amount);
            
            bool run(script output, script input) const;
        
            constexpr static abstractions::machine::definition<machine, script, transaction&> is_script_machine{};
            
        };
        
    }
    
} 

#endif

