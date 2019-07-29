// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/redeem.hpp>
#include <abstractions/transaction.hpp>

namespace abstractions {
    template <typename key, typename script, typename txid>
    typename vertex<key, script, txid>::tx vertex<key, script, txid>::redeem() const {
        tx incomplete = write(); 
        uint size = Inputs.size();
        vector<input> inputs{size};
        for (index i = 0; i < size; i++) inputs[i] = Inputs[i].redeem(incomplete, i);
        return tx::representation{inputs, Outputs};
    }
    
}
