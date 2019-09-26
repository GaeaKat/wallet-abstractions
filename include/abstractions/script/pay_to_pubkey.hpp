// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PAY_TO_PUBKEY
#define ABSTRACTIONS_SCRIPT_PAY_TO_PUBKEY

#include "functions.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/crypto/secp256k1.hpp>

namespace abstractions::script {
    pointer<program> pay_to(const secp256k1::compressed_pubkey&);
    pointer<program> pay_to(const secp256k1::uncompressed_pubkey&);
    pointer<program> redeem_from_pay_to_pubkey(const bitcoin::signature&);
    
    template <typename pubkey>
    struct pay_to_pubkey : public program {
        bytes Script;
        pubkey Pubkey;
        
        static bool valid(bytes);
        
        bool valid() const {
            return valid(Script) && Pubkey.valid();
        }
        
        static pubkey to(bytes& s);
        
        pubkey to() const {
            return Pubkey;
        }
        
        uint32 length() const final override {
            return Script.size();
        }
        
        void write(writer& o) const final override {
            o << Script;
        }
        
        pay_to_pubkey(pubkey p) : Script{pay_to(p)->compile()}, Pubkey{p} {}
        pay_to_pubkey(bytes& b) : Script{b}, Pubkey{to(b)} {}
        
    };
    
    inline pointer<program> pay_to(const secp256k1::compressed_pubkey& p) {
        return sequence({push(p), check_signature()});
    }
    
    inline pointer<program> pay_to(const secp256k1::uncompressed_pubkey& p) {
        return sequence({push(p), check_signature()});
    }
    
    inline pointer<program> redeem_from_pay_to_address(const bitcoin::signature& x) {
        return sequence({push(x)});
    }
    
}

#endif
