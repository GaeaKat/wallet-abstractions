// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include "stage_2.hpp"

namespace abstractions::bitcoin::cosmos::test {
    
    bool test_tx(vector<spendable> prevout, const transaction& tx) {
        if (!tx.valid()) return false;
        if (!valid_scripts(prevout, tx)) return false;
        if (!reasonable_fee(tx)) return false;
        return true;
    }
    
    spendable round(spendable spend, step next) {
        satoshi spent = spend.Output.Value;
        script pay = next.Pattern.pay(next.Key);
        satoshi fee = expected_cost(bitcoin::vertex{{spend}, {output{spent, pay}}});
        if (fee > spent) throw failure{};
        output out{spent - fee, pay};
        transaction tx = vertex{{spend}, {out}}.redeem();
        if (!test_tx({spend}, tx)) throw failure{};
        return spendable{next.Key, out, outpoint{tx.id(), 0}, static_cast<redeemer>(next.Pattern)};
    }
    
}
