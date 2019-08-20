// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>
#include <data/encoding/base58.hpp>
namespace abstractions::bitcoin {

    secret::secret(string wif) {
        bytes sec = data::encoding::base58::read(wif);
        std::copy_n(sec.begin(), 32, this->begin());
    }
        namespace wif {
            bool read(const string&, secret&) {
                throw data::method::unimplemented();
            }
            
            string write(secret&) {
                throw data::method::unimplemented();
            }
            
            bool read(const string&, pubkey&) {
                throw data::method::unimplemented();
            }
            
            string write(pubkey&) {
                throw data::method::unimplemented();
            }
        }
        
        namespace wif_compressed {
            bool read(const string&, secret&) {
                throw data::method::unimplemented();
            }
            
            string write(secret&) {
                throw data::method::unimplemented();
            }
            bool read(const string&, pubkey&) {
                throw data::method::unimplemented();
            }
            
            string write(pubkey&) {
                throw data::method::unimplemented();
            }
        }
        
    }

