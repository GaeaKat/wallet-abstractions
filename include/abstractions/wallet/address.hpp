// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

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
            
            bool operator==(const address& a) const;
            bool operator!=(const address& a) const;
            
            address& operator=(const address& a);
            
            address(const address& a) : parent{static_cast<const parent&>(a)} {}
            address(const pubkey&);
            address(const secret&);
            address(address&&);
            explicit address(const string&);
            
            string write();
            string cashaddr();
        };
        
        namespace bitcoin_address {
            bool read(const string&, ::data::ripemd160::digest&);
            string write(const address&);
        }
        
        namespace cashaddr {
            bool read(const string&, ::data::ripemd160::digest&);
            string write(const address&);
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
            
        inline string address::write() {
            return bitcoin_address::write(*this);
        }
        
        inline string address::cashaddr() {
            return cashaddr::write(*this);
        }
        
        inline address::address(const string& s) {
            bitcoin_address::read(s, static_cast<data::ripemd160::digest&>(*this));
            if (valid()) return;
            cashaddr::read(s, static_cast<data::ripemd160::digest&>(*this));
        }
    }
}

#endif
