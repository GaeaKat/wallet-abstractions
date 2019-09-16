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
        using redeemer = redeem::redeemer<key, script, transaction>;
        using output = redeem::output<script>;
        using outpoint = redeem::outpoint<txid>;
        using debit = redeem::debit<output, outpoint>;
        using input = redeem::input<txid, script>;
        
        key Key;
        redeemer Redeemer;
        
        spendable(output o, outpoint p, key k, redeemer r) : debit{o, p}, Key{k}, Redeemer{r} {}
        spendable(debit d, key k, redeemer r) : debit{d}, Key{k}, Redeemer{r} {}
        
        bool valid() const {
            return debit::valid() && Key.valid() && Redeemer.pay(Key) == debit::Output.script();
        }
        
        input redeem(transaction t, index i) const {
            return input{debit::Outpoint, Redeemer.redeem(value(debit::Output), debit::Output.script(), t, i, Key)};
        }
    };
    
} 

#endif
