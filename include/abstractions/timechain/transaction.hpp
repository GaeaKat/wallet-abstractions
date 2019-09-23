// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TIMECHAIN_TRANSACTION
#define ABSTRACTIONS_TIMECHAIN_TRANSACTION

#include <abstractions/abstractions.hpp>
#include <abstractions/timechain/output.hpp>
#include <abstractions/timechain/input.hpp>

namespace abstractions::timechain::transaction {
    
    template <typename tx, typename Z, typename in, typename out, typename N>
    struct interface {
        
        Z version(tx t) const {
            return t.version();
        }
    
        list<out> outputs(tx t) const {
            return t.outputs();
        }
        
        list<in> inputs(tx t) const {
            return t.inputs();
        }
        
        N locktime(tx t) const {
            return t.locktime();
        }
    
    };
    
    struct serialized {
        slice<byte> Data;
        bool valid() const;
        int32 version();
        list<input::serialized> inputs();
        list<output::serialized> outputs();
        constexpr static interface<serialized, int32, input::serialized, output::serialized, uint32> is_input{};
    };

}   

#endif

