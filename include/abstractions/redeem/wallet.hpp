// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_WALLET
#define ABSTRACTIONS_REDEEM_WALLET

#include "funds.hpp"

namespace abstractions::redeem {
    
    template <typename script, typename txid, typename key, typename tag>
    struct wallet {
        using funds = redeem::funds<script, txid, key>;
        using transaction = typename funds::transaction;
        using unspent = typename funds::unspent;
        using payable = pattern::abstract::addressable<key, script, tag>&;
        
        funds Funds;
        
        wallet() : Funds{}, Pay{} {}
        wallet(list<payable> pay) : Funds{}, Pay{pay} {}
        wallet(funds f, list<payable> pay) : Funds{f}, Pay{pay} {}
        
        // patterns that this wallet knows how to pay to.
        const list<payable> Pay;
        
        bool valid() const {
            return Funds.Valid && Pay.size() > 0;
        }
        
        satoshi balance() const {
            return Funds.Balance;
        }
        
        transaction redeem(queue<data::map::entry<tag, satoshi>> to) const {
            return spend(to).redeem();
        }
        
        unspent spend(queue<data::map::entry<tag, satoshi>> to) const {            
            using output = typename funds::output;
            queue<output> outs{};
            while (!empty(to)) {
                queue<payable> p = Pay;
                while (true) {
                    if (empty(p)) return {};
                    script o = p.first().pay(to.first().key());
                    if (o != script{}) {
                        outs = outs + output{to.first().value(), o};
                        break;
                    } else p = p.rest();
                }
                to = to.rest();
            }
            return Funds.spend(outs);
        }
    };
    
} 

#endif
