// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/address.hpp>

namespace abstractions {
    
    namespace bitcoin {
        
        namespace bitcoin_address {
            bool read(const string&, ::data::ripemd160::digest&) {
                throw 0;
            }
            
            string write(address&) {
                throw 0;
            }
        }
        
        namespace cashaddr {
            bool read(const string&, ::data::ripemd160::digest&) {
                throw 0;
            }
            
            string write(address&) {
                throw 0;
            }
        }
    }
}
