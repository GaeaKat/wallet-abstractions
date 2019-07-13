// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_MACHINE
#define SATOSHI_SV_MACHINE

#include <abstractions/abstractions.hpp>
#include <abstractions/script/machine.hpp>

#include <satoshi_sv/src/script/bitcoinconsensus.h>
#include <satoshi_sv/src/script/script.h>
#include <satoshi_sv/src/script/interpreter.h>

#include <satoshi_sv/sv.hpp>

namespace abstractions::sv {
    
    struct machine {
    private:
        static const uint32_t verify_none = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE;
        static const uint32_t verify_all = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL;
        
        TransactionSignatureChecker Checker;
        uint32_t Flags;
    public:
        // Run machine without checking signatures. 
        machine() : Checker{{}, 0, sv::Amount{0}}, Flags{verify_none} {}
        
        // Run the machine with checking signatures. 
        machine(const CTransaction& tx, index i, satoshi amount) : Checker{&tx, i, sv::Amount{amount}}, Flags{verify_all} {}
        
        bool run(CScript& output, CScript& input) const {
            sv::VerifyScript(input, output, Flags, Checker);
        }
        
    };
    
    constexpr static abstractions::script::machine::interface<machine, CScript&, const CTransaction&> is_script_machine{};
    
} 

#endif
