// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_ADDRESS
#define ABSTRACTIONS_WALLET_ADDRESS

#include <abstractions/crypto/hash/ripemd160.hpp>
#include <abstractions/abstractions.hpp>
#include "tag.hpp"

namespace abstractions::bitcoin {
        
    struct pubkey;
    struct secret;
    
    struct address : public tag {
        using digest = ripemd160::digest;
        digest Digest;
        
        bool operator==(const address& a) const {
            return Digest == a.Digest;
        }
        
        bool operator!=(const address& a) const {
            return Digest != a.Digest;
        }
        
        address& operator=(const address& a);
        
        address()= default;
        explicit address(uint32);
        address(const address& a) : Digest{a.Digest} {}
        
        address(address&& a) : Digest{a.Digest} {
            a = {};
        }
        
        address(const digest& d) : Digest{d} {}
        explicit address(const pubkey&);
        explicit address(const secret&);
        
        static address read(const string&);
        
        explicit address(const string& s) : address{read(s)} {}
        
        string write();
        
        bool valid() const {
            return Digest.valid();
        }
    };
    
    namespace bitcoin_address {
        address read(string&);
        data::string write(const address&);
    }
    
    namespace cashaddr {
        address read(string&);
        data::string write(const address&);
    }
    
    inline address& address::operator=(const address& a) {
        Digest = a.Digest;
        return *this;
    }
    
    inline address address::read(const string& s) {
        address a = bitcoin_address::read(s);
        if (a.valid()) return a;
        return cashaddr::read(s);
    }
    
    inline string address::write() {
        return bitcoin_address::write(*this);
    };
}

inline std::ostream& operator<<(std::ostream& o, abstractions::bitcoin::address& a) {
    return o << "address{" << a.write() << "}";
}

#endif
