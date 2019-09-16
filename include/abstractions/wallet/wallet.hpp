// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_WALLET
#define ABSTRACTIONS_WALLET_WALLET

#include <abstractions/redeem/wallet.hpp>
#include "keys.hpp"
#include "address.hpp"
#include "transaction.hpp"
#include "outpoint.hpp"
#include "spendable.hpp"

namespace abstractions::bitcoin {
    
    using fee_calculator = satoshi (*)(uint32 size, uint32 sigops);
    
    satoshi one_satoshi_per_byte(uint32 size, uint32 sigops) {
        return size;
    }
    
    struct wallet : redeem::wallet<script, txid, secret, tag> {
        using inner = redeem::wallet<script, txid, secret, tag>;
        
        fee_calculator Fees;
        wallet(fee_calculator fees = one_satoshi_per_byte) : inner{}, Fees{fees} {}
        wallet(list<payable> pay, fee_calculator fees = one_satoshi_per_byte) : inner{pay}, Fees{fees} {}
        wallet(funds f, list<payable> pay, fee_calculator fees = one_satoshi_per_byte) : inner{f, pay}, Fees{fees} {}
        
        struct spent;
        
        spent spend(queue<data::map::entry<tag, satoshi>> to, satoshi fee, secret next);
        
        spent spend(queue<data::map::entry<tag, satoshi>> to, secret next);
    };
        
    struct wallet::spent {
        unspent Transaction;
        wallet Remainder;
        
        bool valid() const {
            return Transaction.valid() && Remainder.valid();
        }
        
        friend struct wallet;
    private :
        spent() : Transaction{}, Remainder{} {}
        spent(unspent t, wallet w) : Transaction{t}, Remainder{w} {}
    };

}

#endif
