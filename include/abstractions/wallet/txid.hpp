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
            
            explicit txid(hex s);
            explicit txid(string hex_string);
            
            txid(const txid& t);
            txid(txid&& t);
            txid(parent p);
        };
            
        inline txid::txid(const txid& t) : parent{static_cast<const parent&>(t)} {}
        
        inline txid::txid(txid&& t) : parent{static_cast<parent&&>(t)} {}
        
        inline txid::txid(parent p) : parent{p} {}
        
        inline txid::txid(hex s) : txid{s.valid() ? s.operator bytes() : bytes{}} {}
        
        inline txid::txid(string hex_string) : txid{hex{hex_string}} {}
        
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
