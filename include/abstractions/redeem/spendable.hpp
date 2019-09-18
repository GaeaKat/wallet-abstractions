// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_SPENDABLE
#define ABSTRACTIONS_REDEEM_SPENDABLE

#include "redeem.hpp"
#include "debit.hpp"

namespace abstractions::redeem {
    template <typename script, typename txid, typename key>
    struct spendable : public debit<redeem::output<script>, redeem::outpoint<txid>> {
        using transaction = redeem::transaction<txid, script>;
        using pattern = redeem::pattern<key, script, transaction>&;
        using output = redeem::output<script>;
        using outpoint = redeem::outpoint<txid>;
        using debit = redeem::debit<output, outpoint>;
        using input = redeem::input<txid, script>;
        
        key Key;
        pattern Pattern;
        
        spendable(output o, outpoint p, key k, pattern r) : debit{o, p}, Key{k}, Pattern{r} {}
        spendable(debit d, key k, pattern r) : debit{d}, Key{k}, Pattern{r} {}
        
        bool valid() const {
            return debit::valid() && Key.valid() && Pattern.pay(Key) == debit::Output.script();
        }
        
        input redeem(transaction t, index i) const {
            return input{debit::Outpoint, Pattern.redeem(value(debit::Output), debit::Output.script(), t, i, Key)};
        }
    };
    
} 

#endif
