// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <abstractions/timechain/transaction.hpp>

namespace abstractions::timechain::transaction {
    
    template <typename tx, typename point, typename out>
    satoshi redeemed(index<point, tx>& b, tx t) {
        int r = 0;
        for (point p : outpoints(t)) {
            out prevout = b(p);
            
            if (prevout == out{}) return aleph_0;
                
            r += timechain::output::value(prevout);
        }
        
        return r;
    }

}   

