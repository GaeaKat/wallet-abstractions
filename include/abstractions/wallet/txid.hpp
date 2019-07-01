// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_TXID
#define ABSTRACTIONS_WALLET_TXID

#include <data/crypto/sha512.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct txid : public ::data::sha512::digest {
            using parent = ::data::sha512::digest;
            using parent::digest;
            txid(string hex);
            
            bool operator==(const txid& a) const;
            bool operator!=(const txid& a) const;
            
            txid& operator=(const txid& a);
            
            txid(const txid&);
            txid(txid&&);
            txid(parent);
        };
        
        inline bool txid::operator==(const txid& a) const {
            return uint512::operator==(static_cast<const uint512&>(a));
        }
        
        inline bool txid::operator!=(const txid& a) const {
            return uint512::operator!=(static_cast<const uint512&>(a));
        }
        
        inline txid& txid::operator=(const txid& a) {
            uint512::operator=(static_cast<const uint512&>(a));
            return *this;
        }
        
    }
    
} 

#endif
