// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

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
            machine(const transaction& tx, index i, satoshi amount);
            
            bool run(const script output, const script input) const;
        
            constexpr static abstractions::machine::definition<machine, const script, const transaction&> is_script_machine{};
            
        };
        
    }
    
} 

#endif

