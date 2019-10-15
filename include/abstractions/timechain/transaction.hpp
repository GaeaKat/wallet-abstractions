// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TIMECHAIN_TRANSACTION
#define ABSTRACTIONS_TIMECHAIN_TRANSACTION

#include <abstractions/abstractions.hpp>
#include <abstractions/timechain/output.hpp>
#include <abstractions/timechain/input.hpp>
#include <abstractions/crypto/address.hpp>

namespace abstractions::timechain::transaction {
    
    template <typename tx, typename Z, typename in, typename out, typename N, typename txid>
    struct interface {
        
        Z version(tx t) const {
            return t.version();
        }
    
        queue<out> outputs(tx t) const {
            return t.outputs();
        }
        
        queue<in> inputs(tx t) const {
            return t.inputs();
        }
        
        N locktime(tx t) const {
            return t.locktime();
        }
        
        txid id(tx t) const {
            return t.id();
        }
    
    };
    
    struct serialized {
        bytes_view Data;
        bool valid() const;
        int32 version();
        list<input::serialized> inputs();
        list<output::serialized> outputs();
        int32 locktime();
        sha256::digest id();
        constexpr static interface<serialized, int32, input::serialized, output::serialized, uint32, sha256::digest> is_transaction{};
    };
    
    template <typename tx>
    writer write(writer w, tx t) {
        auto ins = t.inputs();
        auto outs = t.outputs();
        w = (w << int32(t.version())).write_var_int(ins.size());
        while(!empty(ins)) {
            w = input::write(w, ins.first());
            ins = ins.rest();
        }
        w = w.write_var_int(outs.size());
        while(!empty(outs)) {
            w = output::write(w, outs.first());
            outs = outs.rest();
        }
        return w << uint32(t.locktime());
    }
    
    template <typename tx>
    bytes serialize(tx x) {
        bytes b{x.size()};
        writer w{b};
        write(w, x);
        return b;
    }

}   

#endif

