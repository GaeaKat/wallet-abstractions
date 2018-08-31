#ifndef HD_BIP44_HPP
#define HD_BIP44_HPP

#include "bip32.hpp"
#include "hd.hpp"
#include "wallet.hpp"

namespace abstractions
{

namespace hd
{

namespace bip32
{

namespace bip44
{
    
const child_index purpose = hardened_flag + 44;
    
enum coin_type {
    bitcoin_core = 0x80000000, 
    bitcoin_cash = 0x80000091
};
    
typedef child_index account;
    
enum sequence_type {
    External = 0,
    Internal = 1
};
    
typedef child_index index;
    
struct address {
    const coin_type CoinType;
    const account Account;
    const sequence_type SequenceType;
    const index Index;
    
    address(coin_type c, account a, sequence_type t, index i) : CoinType(c), Account(a), SequenceType(t), Index(i) {}
};

derivation<child_index> to_derivation(address address) {
    return pointer<node<child_index>>(new node<child_index>(purpose,
        pointer<node<child_index>>(new node<child_index>(address.CoinType,
            pointer<node<child_index>>(new node<child_index>(address.Account + hardened_flag,
                pointer<node<child_index>>(new node<child_index>(address.SequenceType, 
                    pointer<node<child_index>>(new node<child_index>(address.Index))))))))));
}

//inherets from hd_tools theory and adds a function for finding bip44 addresses. 
template<typename K>
struct theory : public hd::theory<K, child_index> {
    typedef typename hd::theory<K, child_index>::key key;
    
    const key& derive(address address) {
        derivation<child_index> d = to_derivation(address);
        key& k = derive(d);
        return k;
    }
};

const int default_max_future_addresses = 20;

// derive a bunch of keys based on which ones you find have balances in them, according to a bip44 schema. 
template<typename K, typename U>
void generate(const theory<K>& b44, const wallet<K, U>& w, std::vector<coin_type> coins, const int max_future_addresses) {
    for (coin_type c : coins) {
        while (true) {
            uint32_t account = 0;
            uint32_t index = 0;
            typename theory<K>::key& first = b44.derive(address(c, account, External, index));
            
            // We've found all accounts when we find an account whose first key has never received anything.
            if (!w.has_balance(first.Key)) break;
            
            // we have already checked the zeroth address so we can go up one. 
            index++;
            
            // Now generate all the addresses we can find that have a balance. 
            // max_future_addresses is how far we go without finding anything
            // before we stop.
            for (sequence_type t : {External, Internal}) {
                int last_with_balance = 0;
                while (last_with_balance < max_future_addresses) {
                    typename theory<K>::key& k = b44.derive(address(c, account, t, index));
                    
                    if (w.has_balance(k.Key)) {
                        last_with_balance = 0;
                    } else {
                        last_with_balance++;
                    }
                    
                    index++;
                }  
                
                index = 0;
            } 
            
            account++;
        }
    }
}

}

}

}

}

#endif

