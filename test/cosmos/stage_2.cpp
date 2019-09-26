// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include "stage_2.hpp"
#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin::cosmos::test {
    
    wallet run(wallet init, queue<step> steps) {
        return data::fold(&round, init, steps);
    }
    
    wallet round(wallet to_spend, step next) {
        // amount that will be redeemed in this tx. 
        satoshi amount_redeemed = abstractions::value(to_spend);
        satoshi amount_spent = amount_redeemed * 2 / 3;
        
        wallet::spent action = to_spend.spend(
                to_pattern{amount_spent, next.Pattern, next.Key.to_public()}, 
                change{&pay_to_address_compressed, next.Change, one_satoshi_per_byte});
        
        transaction t = action.Transaction;
        if (!t.valid()) throw failure{};
        if (t.outputs().size() != 2) throw failure{};
        if (!valid_scripts(to_spend.Funds.Entries, t)) throw failure{};
        
        transaction rt{action.Transaction};

        return wallet{spendable{rt.Outputs[0], outpoint{t.id(), 0}, next.Key, next.Pattern}};
    }
    
}
