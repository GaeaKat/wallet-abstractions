// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin {
    
    wallet::spent wallet::payment::spend(funds fun) const {
        spend_policy policy = SpendPolicy == unset ? all : SpendPolicy;
        satoshi amount_spent = value();
        funds::taken t = policy == all ? funds::taken{fun, funds{}} : fun.take(amount_spent);
        satoshi amount_redeemed = t.Taken.value();
        unspent un = t.Taken.spend(Payments);
        satoshi fee = Change.Calculator == nullptr ? Change.Fee : Change.Calculator(un.expected_size(), un.signature_operations());
        if (amount_spent + fee > amount_redeemed) return {};
        // no change output has been provided. Therefore the new wallet is empty. 
        if (!Change.valid()) return spent{un.redeem(), {}};
        output& mine = un.Outputs[ChangeIndex];
        mine.Value = amount_redeemed - amount_spent - fee;
        transaction tx = un.redeem();
        return spent{tx, wallet{spendable{mine, outpoint{tx.id(), ChangeIndex}, Change.Key, Change.Pattern}}};
    }

}
