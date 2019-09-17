// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin {
        
    wallet::spent wallet::spend(queue<data::map::entry<tag, satoshi>> to, satoshi fee, secret next) {
        if (!valid()) return {};
        satoshi balance = wallet::value();
        satoshi amount_spent = fee + 
            data::fold(
                [](satoshi p, data::map::entry<tag, satoshi> e)->satoshi{
                    return p + e.Value;
                }, 0, to);
        if (amount_spent > balance) return {};
        
        satoshi change = balance - amount_spent;
        using unspent = inner::unspent; 
        unspent u = inner::spend(to.append(data::map::entry<tag, satoshi>{inner::Pay.first().tag(next), change}));
        if (!u.valid()) return {};
        return spent{u, wallet{funds{queue<spendable>{list<spendable>{} + u.Inputs.last()}}, Pay}};
    }
        
    wallet::spent wallet::spend(queue<data::map::entry<tag, satoshi>> to, secret next) {
        spent no_fee = spend(to, 0, next);
        satoshi fee = Fees(no_fee.Transaction.expected_size(), no_fee.Transaction.signature_operations());
        return spend(to, fee, next); // TODO inefficient.
    }

}
