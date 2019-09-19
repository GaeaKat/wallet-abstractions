// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include "stage_2.hpp"
#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin::cosmos::test {
    
    // test whether the tx is valid. This requires the previous
    // outputs that have been redeemed by it. 
    bool valid_scripts(queue<output> prevout, const transaction& tx);
    
    bool test_tx(queue<output> prevout, const transaction& tx) {
        if (!tx.valid()) return false;
        if (!valid_scripts(prevout, tx)) return false;
        if (!reasonable_fee(tx)) return false;
        return true;
    }
    
    funds run(funds init, queue<step> steps) {
        return data::fold(&round, init, steps);
    }
    
    funds round(funds to_spend, step next) {
        // amount that will be redeemed in this tx. 
        satoshi amount_redeemed = abstractions::value(to_spend);
        satoshi amount_spent = amount_redeemed * 2 / 3;
        
        spent wallet{to_spend}.spend(queue::make(next.Pattern.pay()), change{static_cast<pattern>(pay_to_address_compressed), next.Change});
        //, queue<pattern>::make(next.Pattern), one_satoshi_per_byte}.spend({}, next.Key);

        satoshi fee = expected_cost(redeem::vertex{{to_spend}, {output{spent, pay}}});
        if (fee > spent) throw failure{};
        output out{spent - fee, pay};
        transaction tx = redeem::vertex{{to_spend}, {out}}.redeem();
        if (!test_tx({spend}, tx)) throw failure{};
        return spendable{next.Key, out, outpoint{tx.id(), 0}, next.Pattern};
    }
    
}
