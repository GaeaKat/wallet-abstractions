// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SATOSHI_SV_MACHINE
#define SATOSHI_SV_MACHINE

#include <abstractions/abstractions.hpp>
#include <abstractions/fundamental.hpp>
#include <sv/src/script/interpreter.h>
#include <sv/src/script/bitcoinconsensus.h>
#include <sv/src/primitives/transaction.h>

namespace abstractions {

    namespace satoshi_sv {
        
        template <typename script, typename tx> struct machine;
        
        template <>
        struct machine<CScript&, CTransaction> {
        private:
            TransactionSignatureChecker Checker;
            uint32_t Flags;
        public:
            // Run machine without checking signatures. 
            machine() : Checker{{}, 0, 0}, Flags{bitcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE} {}
            
            // Run the machine with checking signatures. 
            machine(CTransaction tx, index i, satoshi amount) : Checker{tx, i, amount}, Flags{bitcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL} {}
            
            bool run(CScript& output, CScript& input) const {
                EvalScript(input, output, Flags, Checker);
            }
            
        };
            
    }
    
} 

#endif
