// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <bitcoin/system/wallet/payment_address.hpp>
#include <abc/src/cashaddr.h>

namespace abstractions {
    
    namespace bitcoin {
        
        address::address(const pubkey& p) : address{p.address()} {};
        
        address::address(const secret& s) : address{s.address()} {};
        
        namespace bitcoin_address {
            bool read(const string& base58, ::data::ripemd160::digest& d) {
                libbitcoin::system::wallet::payment_address addr{base58};
                if (!addr) return false;
                d = libbitcoin::system::short_hash{addr};
                return true;
            }
            
            string write(const address& a) {
                return libbitcoin::system::wallet::payment_address{a}.encoded();
            }
        }
        
        namespace cashaddr {
            string prefix = "prefix";
            bool read(const string& s, ::data::ripemd160::digest& d) {
                auto p = abc::cashaddr::Decode(s, prefix);
                if (p.first == "") return false;
                d = ::data::ripemd160::digest{p.second};
                return true;
            }
            
            string write(const address& a) {
                std::vector<byte> v{20};
                std::copy(a.begin(), a.end(), v.begin());
                return abc::cashaddr::Encode("", v);
            }
        }
    }
}
