// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>
#include <data/encoding/base58.hpp>
namespace abstractions::bitcoin {

    secret::secret(string wif) {
        if (!wif::read(wif, *this)) if (!wif_uncompressed::read(wif, *this) *this = {};
    }
    
    pubkey::pubkey(string hex) {
        bytes sec = data::encoding::hex::string(hex);
        std::copy_n(sec.begin(), 33, Pubkey.begin());
    };

    uncompressed_pubkey::uncompressed_pubkey(string hex) {
        bytes sec = data::encoding::hex::string(hex);
        std::copy_n(sec.begin(), 65, Pubkey.begin());
    }
    
    namespace wif {
        bool read(const string&, secret&) {
            throw data::method::unimplemented();
        }
        
        string write(const secret&) {
            throw data::method::unimplemented();
        }
        
        bool read(const string&, pubkey&) {
            throw data::method::unimplemented();
        }
        
        string write(const pubkey&) {
            throw data::method::unimplemented();
        }
    }
        
    namespace wif_uncompressed {
        bool read(const string&, secret&) {
            throw data::method::unimplemented();
        }
        
        string write(const secret&) {
            throw data::method::unimplemented();
        }
    
        bool read(const string&, uncompressed_pubkey&) {
            throw data::method::unimplemented();
        }
        
        string write(const uncompressed_pubkey&) {
            throw data::method::unimplemented();
        }
    }


}

