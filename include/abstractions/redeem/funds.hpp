// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_REDEEM_FUNDS
#define ABSTRACTIONS_REDEEM_FUNDS

#include "unspent.hpp"

namespace abstractions::redeem {
    
    template <typename script, typename txid, typename secret, typename pubkey>
    struct funds {
        using unspent = redeem::unspent<script, txid, secret, pubkey>;
        using spendable = typename redeem::spendable<script, txid, secret, pubkey>;
        
        const queue<spendable> Entries;
        const satoshi Value;
        const bool Valid;
        
        static satoshi value(const queue<spendable> entries) {
            return fold([](satoshi b, spendable s)->satoshi{return b + abstractions::value(s);}, satoshi{0}, entries);
        }
        
        static bool valid(const queue<spendable> entries) {
            return fold([](bool b, spendable s)->bool{return b && s.valid();}, true, entries);
        }
        
        funds() : Entries{}, Value{0}, Valid{true} {}
        funds(spendable e) : Entries{queue<spendable>::make(e)}, Value{abstractions::value(e)}, Valid{e.valid()} {}
        funds(const queue<spendable> e) : Entries{e}, Value{value(e)}, Valid{valid(e)} {}
        
        funds import(spendable s) const {
            return {Entries + s, Value + value(s), Valid && s.valid()};
        }
        
        satoshi value() const {
            return Value;
        }
        
        using transaction = typename unspent::transaction;
        using output = typename unspent::out;
        
        unspent spend(queue<output> o) const {
            if (!Valid) return {};
            return unspent{Entries, o};
        }
        
        transaction redeem(queue<output> o) const {
            return spend(o).redeem();
        }
        
    private:
        funds(const queue<spendable> e, const satoshi b) : Entries{e}, Value{b} {}
    };
    
} 

#endif
