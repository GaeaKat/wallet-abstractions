// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <abstractions/crypto/hash/ripemd160.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/abstractions.hpp>
#include "tag.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey;
        struct secret;
        
        struct address : public ::data::ripemd160::digest, public tag {
            using parent = ::data::ripemd160::digest;
            using parent::digest;
            
            static address read(string formated);
            
            bool operator==(const address& a) const;
            bool operator!=(const address& a) const;
            
            address& operator=(const address& a);
            
            address(const address&);
            address(address&&);
            address(pubkey&);
            address(secret&);
        };
        
        namespace bitcoin_address {
            bool read(stringstream&, address&);
            string write(address&);
            void write(address&, stringstream&);
        }
        
        namespace cashaddr {
            bool read(stringstream&, address&);
            string write(address&);
            void write(address&, stringstream&);
        }
        
        inline bool address::operator==(const address& a) const {
            return parent::operator==(static_cast<const parent&>(a));
        }
        
        inline bool address::operator!=(const address& a) const {
            return parent::operator!=(static_cast<const parent&>(a));
        }
        
        inline address& address::operator=(const address& a) {
            parent::operator=(static_cast<const parent&>(a));
            return *this;
        }
    }
}

#endif
