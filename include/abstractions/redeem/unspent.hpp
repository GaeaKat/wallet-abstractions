// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_UNSPENT
#define ABSTRACTIONS_REDEEM_UNSPENT

#include "spendable.hpp"
#include <abstractions/redeem/vertex.hpp>

namespace abstractions::redeem {
    template <typename script, typename txid, typename secret, typename pubkey>
    struct unspent : redeem::vertex<spendable<script, txid, secret, pubkey>, redeem::output<script>> {
        using out = redeem::output<script>;
        using point = redeem::outpoint<txid>;
        using debit = redeem::debit<out, point>;
        using in = spendable<script, txid, secret, pubkey>;
        using vertex = redeem::vertex<in, out>;
        using vertex::vertex;
        
        uint32 expected_size() const {
            return fold([](satoshi v, in x)->satoshi{
                return x.expected_size() + v;
            }, uint32{0}, vertex::Inputs);
        }
        
        uint32 signature_operations() const {
            return fold([](satoshi v, in x)->satoshi{
                return x.signature_operations() + v;
            }, uint32{0}, vertex::Inputs);
        }
        
        using transaction = redeem::transaction<txid, script>;
        
        transaction redeem() const;
    private:
        transaction write() const;
    };
    
    template <typename script, typename txid, typename secret, typename pubkey>
    transaction<txid, script> unspent<script, txid, secret, pubkey>::redeem() const {
        using input = redeem::input<txid, script>;
        transaction incomplete = write(); 
        index i = 0;
        return transaction{for_each([&incomplete, &i](spendable<script, txid, secret, pubkey> s)->input{
            return s.redeem(input_index<transaction>{incomplete, i++});
        }, vertex::Inputs), vertex::Outputs};
    }
    
} 

#endif
