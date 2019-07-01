// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <abstractions/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/abstractions.hpp>
#include "tag.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct pubkey;
        struct secret;
        
        struct address : public ::data::sha256::digest, public tag {
            using parent = ::data::sha256::digest;
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
            return uint256::operator==(static_cast<const uint256&>(a));
        }
        
        inline bool address::operator!=(const address& a) const {
            return uint256::operator!=(static_cast<const uint256&>(a));
        }
        
        inline address& address::operator=(const address& a) {
            uint256::operator=(static_cast<const uint256&>(a));
            return *this;
        }
    }
}

#endif
