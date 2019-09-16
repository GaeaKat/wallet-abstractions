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
    
    struct wallet : redeem::wallet<script, txid, secret, tag> {
        using inner = redeem::wallet<script, txid, secret, tag>;
        using inner::wallet;
        
        struct spent;
        
        spent spend(queue<data::map::entry<tag, satoshi>> to, satoshi fee, secret next);
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
