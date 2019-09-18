// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_WALLET
#define ABSTRACTIONS_WALLET_WALLET

#include <abstractions/redeem/funds.hpp>
#include "payment.hpp"
#include "outpoint.hpp"

namespace abstractions::bitcoin {
    
    using fee_calculator = satoshi (*)(uint32 size, uint32 sigops);
    
    satoshi one_satoshi_per_byte(uint32 size, uint32 sigops) {
        return size;
    }
    
    struct change {
        pattern Pattern;
        secret Key;
        
        output pay(satoshi value) const {
            return output{value, Pattern.pay(Key)};
        }
    };
    
    using funds = redeem::funds<script, txid, secret>;
    using to = queue<pointer<payment>>;
    
    unspent spend(funds, to);
    
    struct wallet {
        funds Funds;
        
        wallet() : Funds{} {}
        wallet(funds f) : Funds{f} {}
        wallet(spendable x) : Funds{x} {}
        
        bool valid() const {
            return Funds.Valid;
        }
        
        bool value() const {
            return Funds.Value;
        }
        
        struct spent;
        
        // provide a means of creating a change output and 
        // ensure that the mining fee is the fee that is given. 
        spent spend(to out, change next, satoshi fee) const;
        
        // provide a fee calculator instead. 
        spent spend(to out, change next, fee_calculator fees = one_satoshi_per_byte) const;
    };
    
    struct wallet::spent {
        transaction Transaction;
        wallet Remainder;
        
        bool valid() const {
            return Transaction.valid() && Remainder.valid();
        }
        
        friend struct wallet;
    private :
        spent() : Transaction{}, Remainder{} {}
        spent(transaction t, wallet w) : Transaction{t}, Remainder{w} {}
    };

}

#endif
