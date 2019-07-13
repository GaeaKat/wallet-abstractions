// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_MACHINE
#define SATOSHI_SV_MACHINE

#include <abstractions/script/machine.hpp>

#include <satoshi_sv/src/script/bitcoinconsensus.h>
#include <satoshi_sv/src/script/script.h>

#include <satoshi_sv/sv.hpp>

namespace abstractions::sv {
    
    struct sv_machine {
    private:
        static const uint32_t verify_none = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE;
        static const uint32_t verify_all = bitcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL;
        
        TransactionSignatureChecker Checker;
        uint32_t Flags;
    public:
        // Run machine without checking signatures. 
        sv_machine() : Checker{{}, 0, sv::Amount{0}}, Flags{verify_none} {}
        
        // Run the machine with checking signatures. 
        sv_machine(const CTransaction& tx, index i, satoshi amount) : Checker{&tx, i, sv::Amount{amount}}, Flags{verify_all} {}
        
        bool run(const CScript& output, const CScript& input) const {
            sv::VerifyScript(input, output, Flags, Checker);
        }
        
    };
    
    constexpr static abstractions::script::machine::interface<sv_machine, CScript&, const CTransaction&> sv_machine_is_machine{};
    
    struct machine {
    private:
        sv_machine Machine;
    public:
        machine() : Machine{} {}
        
        // Run the machine with checking signatures. 
        machine(bitcoin::transaction& tx, index i, satoshi amount) : Machine{convert(tx), i, amount} {}
        
        bool run(bitcoin::script& output, bitcoin::script& input) const {
            return Machine.run(convert(output), convert(input));
        }
        
    };
    
    constexpr static abstractions::script::machine::interface<machine, bitcoin::script&, bitcoin::transaction&> machine_is_machine{};
    
} 

#endif
