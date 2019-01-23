#ifndef HD_BIP44_HPP
#define HD_BIP44_HPP

#include "bip32.hpp"
#include "hd.hpp"
#include <abstractions/data.hpp>

namespace abstractions
{

    namespace hd
    {

        namespace bip44
        {
            
            const bip32::child_index purpose = bip32::hardened_flag + 44;
                
            enum coin_type {
                BTC = 0x80000000, 
                BCH = 0x80000091, 
                BSV = 0x80000000
            };
                
            enum sequence_type {
                External = 0,
                Internal = 1
            };
                
            typedef bip32::child_index index;
                
            struct address {
                const coin_type CoinType;
                const index Account;
                const sequence_type SequenceType;
                const index Index;
                
                address(coin_type c, index a, sequence_type t, index i) : CoinType(c), Account(a), SequenceType(t), Index(i) {}
            };

            bip32::derivation to_derivation(address address) {
                return bip32::derivation{} + purpose + address.CoinType + (address.Account + bip32::hardened_flag) + address.SequenceType + address.Index;
            }

            //inherets from theory and adds a function for finding bip44 addresses. 
            template<typename K>
            struct tree : public hd::tree<K> {
                typedef typename hd::tree<K>::key key;
                
                const key& derive(address address) {
                    bip32::derivation d = to_derivation(address);
                    key& k = derive(d);
                    return k;
                }
            };

        }

    }

}

#endif

