// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_UNSPENT
#define ABSTRACTIONS_REDEEM_UNSPENT

#include "spendable.hpp"
#include "vertex.hpp"

namespace abstractions::redeem {
    
    template <typename script, typename txid, typename key>
    struct unspent : vertex<spendable<script, txid, key>, redeem::output<script>> {
        
        using output = redeem::output<script>;
        using outpoint = redeem::outpoint<txid>;
        using debit = redeem::debit<output, outpoint>;
        
        using vertex<spendable<script, txid, key>, output>::vertex;
        
        uint32 expected_size() const;
        uint32 signature_operations() const;
        
        using transaction = redeem::transaction<txid, script>;
        
        transaction redeem() const;
    private:
        transaction write() const;
    };
    
    template <typename script, typename txid, typename key>
    transaction<txid, script> unspent<script, txid, key>::redeem() const {
        using vertex = vertex<debit, output>;
        using input = redeem::input<txid, script>;
        transaction incomplete = write(); 
        list<input> Inputs = vertex::Inputs;
        uint size = vertex::Inputs.size();
        vector<input> inputs{size};
        for (index i = 0; i < size; i++) {
            inputs[i] = vertex::Inputs.first().redeem(incomplete, i);
            Inputs = Inputs.rest();
        }
        return transaction{inputs, vertex::Outputs};
    }
    
} 

#endif
