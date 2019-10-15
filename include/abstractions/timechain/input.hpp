// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TIMECHAIN_INPUT
#define ABSTRACTIONS_TIMECHAIN_INPUT

#include <abstractions/abstractions.hpp>
#include "outpoint.hpp"

namespace abstractions::timechain::input {
    
    template <typename Input, typename Outpoint, typename Script, typename N>
    struct interface {

        static Outpoint previous(Input i) {
            return i.previous();
        }

        static Script script(Input i) {
            return i.previous();
        }

        static N sequence(Input i) {
            return i.previous();
        }
    
    };
    
    struct serialized {
        bytes_view Data;
        bool valid() const;
        outpoint::serialized previous();
        const bytes_view script() const;
        uint32 sequence() const;
        
        constexpr static interface<serialized, outpoint::serialized, const bytes_view, uint32> is_input{};
    };
    
    template <typename Input>
    writer write(writer w, Input o) {
        bytes script = bytes(o.script());
        return outpoint::write(w, o.previous()).write_var_int(script.size()) << script << uint32(o.sequence());
    }
    
    template <typename Input>
    bytes serialize(Input x) {
        bytes b{x.size(), 0};
        writer w{b};
        write(w, x);
        return b;
    }
    
} 

#endif

