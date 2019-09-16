// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_FUNDS
#define ABSTRACTIONS_REDEEM_FUNDS

#include "unspent.hpp"

namespace abstractions::redeem {
    
    template <typename script, typename txid, typename key>
    struct funds {
        using unspent = redeem::unspent<script, txid, key>;
        using spendable = typename redeem::spendable<script, txid, key>;
        
        const queue<spendable> Entries;
        const satoshi Balance;
        const bool Valid;
        
        static satoshi balance(const queue<spendable> entries) {
            return fold([](satoshi b, spendable s)->satoshi{return b + value<spendable>(s);}, satoshi{0}, entries);
        }
        
        static bool valid(const queue<spendable> entries) {
            return fold([](bool b, spendable s)->bool{return b && s.valid();}, true, entries);
        }
        
        funds() : Entries{}, Balance{0}, Valid{true} {}
        funds(const queue<spendable> e) : Entries{e}, Balance{balance(e)}, Valid{valid(e)} {}
        
        funds import(spendable s) const {
            return {Entries + s, Balance + value(s), Valid && s.valid()};
        }
        
        using transaction = typename unspent::transaction;
        using output = typename unspent::output;
        
        unspent spend(queue<output> o) const {
            if (!Valid) return {};
            return unspent{Entries, o};
        }
        
        transaction redeem(queue<output> o) const {
            return spend(o).redeem();
        }
    private:
        funds(const queue<spendable> e, const satoshi b) : Entries{e}, Balance{b} {}
    };
    
} 

#endif
