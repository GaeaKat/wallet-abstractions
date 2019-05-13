// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET
#define ABSTRACTIONS_WALLET

#include <abstractions/pattern.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    template <typename out, typename point>
    struct debit {
        out Output;
        point Point;
    };
        
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>
    struct funds {
        using spendable = data::map::entry<tag, debit<out, point>>;
        using recognizable = pattern::abstract::recognizable<key, script, tag, tx, machine>&;
        
        satoshi Balance;
        
        list<recognizable> Recognize;
        
        list<key> Keys;
            
        list<debit<out, point>> Entries;
            
        map<tag, key> Tags; 
        
        funds import(key);
        
        // Look for any inputs that redeem outputs in our funds
        // and any outputs that we can add to our funds. 
        funds update(tx t);
        
        funds(list<recognizable> r) : Balance{empty}, Recognize{r} {}
            
    };
        
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine> 
    struct wallet {
        using funds = abstractions::funds<key, tag, script, out, point, tx, machine>; 
        using payable = pattern::abstract::addressable<key, script, tag, tx, machine>&;
        using recognizable = typename funds::recognizable;
        
        // funds available to spend in this wallet. 
        funds Funds;
        
        // patterns that this wallet knows how to pay to.
        list<payable> Pay;
        
        // index of pattern that generates change scripts. 
        index Change;
        
        list<key> Source;
        
        bool valid() const {
            return Funds.valid() && data::size(Pay) <= Change && Change >= 1 && data::size(Source) >= 1;
        }
        
        struct spent {
            tx Transaction;
            wallet Remainder;
                        
            bool valid() const {
                return Transaction.valid() && Remainder.valid();
            }
            
        private :
            spent() : Transaction{}, Remainder{} {}
            spent(tx t, wallet w) : Transaction{t}, Remainder{w} {}
        };
        
        spent spend(list<data::map::entry<tag, satoshi>> to, satoshi fee) const;
            
        wallet(funds f, list<payable> pay, index change, 
            list<key> source) : Funds{f}, Pay{pay}, Change{change}, Source{source} {}
    };
    
}

#endif
