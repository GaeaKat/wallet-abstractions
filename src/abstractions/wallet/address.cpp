// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <bitcoin/system/wallet/payment_address.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        address::address(const pubkey& p) : address{p.address()} {};
        
        address::address(const secret& s) : address{s.address()} {};
        
        namespace bitcoin_address {
            bool read(const string& base58, ::data::ripemd160::digest& d) {
                libbitcoin::system::wallet::payment_address addr{base58};
                if (!addr) return false;
                libbitcoin::system::short_hash hash{addr};
                std::copy(hash.begin(), hash.end(), d.begin());
                return true;
            }
            
            string write(const address& a) {
                return libbitcoin::system::wallet::payment_address{a}.encoded();
            }
        }
        
        namespace cashaddr {
            bool read(const string&, ::data::ripemd160::digest&) {
                throw 0;
            }
            
            string write(const address&) {
                throw 0;
            }
        }
    }
}
