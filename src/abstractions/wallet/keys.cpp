// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/keys.hpp>

namespace abstractions {
    
    namespace bitcoin {
    
        namespace wif {
            bool read(string&, secret&) {
                throw 0;
            }
            
            string write(secret&) {
                throw 0;
            }
            
            void write(secret&, stringstream&) {
                throw 0;
            }
        }
        
        namespace wif_compressed {
            bool read(string&, secret&) {
                throw 0;
            }
            
            string write(secret&) {
                throw 0;
            }
            
            void write(secret&, stringstream&) {
                throw 0;
            }
        }
        
    }
    
} 

