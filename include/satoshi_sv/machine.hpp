// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SATOSHI_SV_MACHINE
#define SATOSHI_SV_MACHINE

#include <abstractions/machine.hpp>
#include <abstractions/fundamental.hpp>

#include <satoshi_sv/src/script/bitcoinconsensus.h>
#include <satoshi_sv/src/script/script.h>
#include <satoshi_sv/src/script/interpreter.h>

namespace abstractions {

    namespace machine {
        
        using TransactionSignatureChecker = satoshi_sv::TransactionSignatureChecker;
        using CTransaction = satoshi_sv::CTransaction;
        using CScript = satoshi_sv::CScript;
        
        struct sv_machine {
        private:
            static const uint32_t verify_none = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE;
            static const uint32_t verify_all = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL;
            
            TransactionSignatureChecker Checker;
            uint32_t Flags;
        public:
            // Run machine without checking signatures. 
            sv_machine() : Checker{{}, 0, 0}, Flags{verify_none} {}
            
            // Run the machine with checking signatures. 
            sv_machine(CTransaction tx, index i, satoshi amount) : Checker{tx, i, amount}, Flags{verify_all} {}
            
            bool run(CScript& output, CScript& input) const {
                satoshi_sv::EvalScript(input, output, Flags, Checker);
            }
            
        };
        
        constexpr static abstractions::machine::definition<sv_machine, CScript&, CTransaction> is_script_machine{};
            
    }
    
} 

#endif
