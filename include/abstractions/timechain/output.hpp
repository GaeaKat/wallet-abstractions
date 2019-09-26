// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_BITCOIN_OUTPUT
#define ABSTRACTIONS_BITCOIN_OUTPUT

#include <abstractions/abstractions.hpp>
#include "timechain.hpp"

namespace abstractions::timechain::output {
    
    template <typename Output, typename Satoshi, typename Script>
    struct interface {
    
        // How much is stored in a given output?
        static Satoshi value(Output o) {
            return o.value();
        }
            
        // What is the script defining how this output is redeemed. 
        static Script script(Output o) {
            return o.script();
        }
        
    };
    
    struct serialized {
        slice<byte> Data;
        bool valid() const;
        satoshi value() const;
        const slice<byte> script() const;
        
        constexpr static interface<serialized, satoshi, const slice<byte>> is_output{};
    };
    
    template <typename Output>
    writer write(writer w, Output o) {
        bytes script = bytes(o.script());
        return (w << satoshi(o.value())).write_var_int(script.size()) << script;
    }
    
    template <typename Output>
    bytes serialize(Output x) {
        bytes b{x.size(), 0};
        writer w{b};
        write(w, x);
        return b;
    }
    
} 

#endif
