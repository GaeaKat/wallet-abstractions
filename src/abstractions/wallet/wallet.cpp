// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin {
    unspent spend(funds f, to out) {
        satoshi balance = f.value();
        satoshi amount_spent = 
            data::fold(
                [](satoshi p, pointer<payment> e)->satoshi{
                    return p + e->Value;
                }, 0, out);
        if (amount_spent > balance) return {};
        
        queue<output> outs{};
        while (!empty(out)) {
            output o = out.first()->pay();
            if (!o.valid()) return {};
            out = out.rest();
            outs = outs.append(o);
        }
        return f.spend(outs);
    }
    
    wallet::spent wallet::spend(to out, change next, satoshi fee) const {
        output mine = next.pay(fee);
        unspent u = bitcoin::spend(Funds, out.append(std::make_shared<to_script>(mine)));
        if (!u.valid()) return {};
        transaction t = u.redeem();
        return spent{t, wallet{spendable{mine, outpoint{crypto::txid(t), t.outputs().size()}, next.Key, next.Pattern}}};
    }
    
    wallet::spent wallet::spend(to out, change next, fee_calculator fees) const {
        output remainder = next.pay(0);
        unspent no_fee = bitcoin::spend(Funds, out.append(std::make_shared<to_script>(remainder)));
        satoshi fee = fees(no_fee.expected_size(), no_fee.signature_operations());
        return spend(out, next, fee);
    }

}
