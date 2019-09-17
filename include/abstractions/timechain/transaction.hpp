// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_TIMECHAIN_TRANSACTION
#define ABSTRACTIONS_TIMECHAIN_TRANSACTION

#include <abstractions/abstractions.hpp>
#include <abstractions/association.hpp>
#include <abstractions/timechain/output.hpp>

namespace abstractions::timechain::transaction {
    
    template <typename tx, typename in, typename out>
    struct interface {
    
        slice<out> outputs(tx t) const {
            return t.outputs();
        }
        
        slice<in> inputs(tx t) const {
            return t.inputs();
        }
        
        uint32 locktime(tx t) const {
            return t.locktime();
        }
        
        int32 version(tx t) const {
            return t.version();
        }
        
        satoshi fee(tx t) const {
            return t.fee();
        }
    
    };
        
    template <typename point, typename tx>
    using index = association<point, tx>;
    
    template <typename tx, typename point, typename out>
    satoshi redeemed(index<point, tx>& b, tx t);
    
    template <typename tx, typename point, typename out>
    inline satoshi spent(tx t) {
        int r = 0;
        for (out p : outputs(t)) r += timechain::output::value(p);
        return r;
    }
    
    template <typename tx, typename index>
    inline int32 fee(index b, tx t) {
        int32 redeemed = redeemed(b, t);
        if (redeemed == 0) return 0;
        return redeemed - spent(t);
    }

    template <typename tx, typename index>
    inline bool positive(tx t, index b) {
        return fee(t, b) > 0;
    }

}   

#endif

