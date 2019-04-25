// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <abstractions/wallet.hpp>
#include <abstractions/redeem.hpp>

#include <data/for_each.hpp>
#include <data/fold.hpp>

namespace abstractions {
    
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>     
    typename wallet<key, tag, script, out, point, tx, machine>::spent wallet<key, tag, script, out, point, tx, machine>::spend(list<data::map::entry<tag, satoshi>> to, satoshi fee) const {
        satoshi spent = fee + 
            data::reduce(
                [](satoshi p, data::map::entry<tag, satoshi> e)->satoshi{
                    p + e.Value;
                }, to);
        if (spent > Funds.Balance) return {};
        
        satoshi change = Funds.Balance - spent; 
        key next = data::first(Source);
        
        list<out> outputs{
            data::for_each(
                [&](data::map::entry<tag, satoshi> e)->out{
                    for (payable p : Pay) {
                        script pay_to = p.pay(e.Key);
                        if (pay_to != script{}) return {e.Value, pay_to};
                    }
                    return {};
                }, 
                data::append(to, data::map::entry<tag, satoshi>{Pay[Change].tag(next), change}))};
        
        using vertex = vertex<key, out, point>;
        using vertex_spendable = typename vertex::spendable;
        
        list<vertex_spendable> inputs{
            data::for_each(
                [&](debit<out, point> x)->vertex_spendable{
                    for(recognizable r : Funds.Recognize) {
                        tag addr = r.tag(x.Output.ScriptPubKey);
                        if (addr != tag{}) return {Funds.Keys[addr], x.Output, x.Point};
                    } 
                    return {};
                }, 
                Funds.Entries)};
        
        tx t = redeem(Funds.Recognize, vertex{inputs, outputs});
        return {t, {funds{Funds.Recognize}.import(next).update(t), Pay, Change, data::rest(Source)}};
    };
    
}
