#ifndef HD_BIP44_HPP
#define HD_BIP44_HPP

#include "bip32.hpp"
#include "hd.hpp"

namespace hd_tools
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
    
enum internal {
    no = 0,
    yes = 1
};
    
typedef child_index index;
    
struct address {
    const coin_type CoinType;
    const account Account;
    const internal Internal;
    const index Index;
};

derivation<child_index> to_derivation(address address) {
    return new node<child_index>(purpose,
        new node<child_index>(address.CoinType,
            new node<child_index>(address.Account + hardened_flag,
                new node<child_index>(address.Internal, 
                    new node<child_index>(address.Index, nullptr)))));
}

//inherets from hd_tools theory and adds a function for finding bip44 addresses. 
template<typename K>
struct theory : public hd_tools::theory<K, child_index> {
    typedef typename hd_tools::theory<K, child_index>::key key;
    
    const key& derive(address address) {
        derivation<child_index> d = to_derivation(address);
        key& k = derive(d);
        delete d;
        return k;
    }
};

}

}

}

#endif

