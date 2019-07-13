// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_TXID
#define ABSTRACTIONS_WALLET_TXID

#include <data/crypto/sha512.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        struct txid : public ::data::sha512::digest {
            using parent = ::data::sha512::digest;
            using parent::digest;
            
            bool operator==(const txid& a) const;
            bool operator!=(const txid& a) const;
            
            txid& operator=(const txid& a);
            
            txid(hex s) : txid{s.valid() ? bytes(s) : bytes{}} {}
            txid(string hex_string) : txid{hex{hex_string}} {}
            txid(bytes b);
            
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
