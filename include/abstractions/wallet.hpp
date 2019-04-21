#ifndef ABSTRACTIONS_WALLET_BASIC
#define ABSTRACTIONS_WALLET_BASIC

#include <abstractions/pattern.hpp>
#include <abstractions/data.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    template <typename out, typename point>
    struct entry {
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
    struct account {
        satoshi Balance;
            
        list<pattern::abstract::recognizable<key, script, tag, tx, machine>&> Patterns;
            
        list<key> Keys;
            
        map<tag, key> Tags;
            
        map<entry<out, point>, tag> Entries;
            
        account import_key(key);
            
        account update(tx t);
            
    };
        
    template <
        typename key, 
        typename tag, 
        typename script,
        typename out, 
        typename point, 
        typename tx, 
        typename machine> 
    tx redeem(
        list<pattern::abstract::addressable<key, script, tag, tx, machine>&>,
        account<key, tag, script, out, point, tx, machine>, 
        list<data::map::entry<tag, satoshi>>);
        
    template <
        typename key,
        typename tag,
        typename script,
        typename out, 
        typename point, 
        typename tx,
        typename machine>
    struct wallet {
        account<key, tag, script, out, point, tx, machine> Funds;
        
        list<key> Change;
        
        struct spent {
            tx Transaction;
            wallet Remainder;
                        
            bool valid() const {
                return Transaction.valid() && Remainder.valid();
            }
        };
        
        spent spend();
    };
    
}

#endif
