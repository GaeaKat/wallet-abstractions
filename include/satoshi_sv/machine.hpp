// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_MACHINE
#define SATOSHI_SV_MACHINE

#include <abstractions/script/machine.hpp>

namespace abstractions::sv {
    
    struct machine {
    private:
        input_index<bytes_view> Input; 
        satoshi Amount;
    public:
        machine() : Input{}, Amount{0} {}
        
        // Run the machine with checking signatures. 
        machine(input_index<bytes_view> i, satoshi amount) : Input{i}, Amount{amount} {}
        
        bool run(bytes_view output, bytes_view input) const;
        
    };
    
    constexpr static abstractions::script::machine::interface<machine, bytes_view, bytes_view> machine_is_machine{};
    
} 

#endif
