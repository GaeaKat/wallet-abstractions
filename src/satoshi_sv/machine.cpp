// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <satoshi_sv/machine.hpp>

#include <script/bitcoinconsensus.h>
#include <script/script.h>

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
        sv_machine() : Checker{{}, 0, Amount{0}}, Flags{verify_none} {}
        
        // Run the machine with checking signatures. 
        sv_machine(input_index<CTransaction> tx, satoshi amount) : Checker{&tx.Transaction, tx.Index, Amount{amount}}, Flags{verify_all} {}
        
        bool run(const CScript& output, const CScript& input) const {
            return VerifyScript(input, output, Flags, Checker);
        }
        
    };
    
    constexpr static abstractions::script::machine::interface<sv_machine, CScript&, const CTransaction&> sv_machine_is_machine{};
    
    bool machine::run(bytes_view output, bytes_view input) const {
        return sv_machine{input_index<CTransaction>{read_transaction(Input.Transaction), Input.Index}, Amount}.run(read_script(output), read_script(input));
    }
    
} 

