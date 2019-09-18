// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_UNSPENT
#define ABSTRACTIONS_REDEEM_UNSPENT

#include "spendable.hpp"
#include <abstractions/transaction.hpp>

namespace abstractions::redeem {
    template <typename script, typename txid, typename key>
    struct unspent : abstractions::vertex<spendable<script, txid, key>, redeem::output<script>> {
        using output = redeem::output<script>;
        using outpoint = redeem::outpoint<txid>;
        using debit = redeem::debit<output, outpoint>;
        using vertex = abstractions::vertex<spendable<script, txid, key>, redeem::output<script>>;
        using vertex::vertex;
        
        uint32 expected_size() const;
        uint32 signature_operations() const;
        
        using transaction = redeem::transaction<txid, script>;
        
        transaction redeem() const;
    private:
        transaction write() const;
    };
    
    template <typename script, typename txid, typename key>
    transaction<txid, script> unspent<script, txid, key>::redeem() const {
        using input = redeem::input<txid, script>;
        transaction incomplete = write(); 
        index i = 0;
        return transaction{for_each([&incomplete, &i](spendable<script, txid, key> s)->input{
            return s.redeem(incomplete, i++);
        }, vertex::Inputs), vertex::Outputs};
    }
    
} 

#endif
