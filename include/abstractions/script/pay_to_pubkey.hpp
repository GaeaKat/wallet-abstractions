// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PAY_TO_PUBKEY
#define ABSTRACTIONS_SCRIPT_PAY_TO_PUBKEY

#include "functions.hpp"
#include "push.hpp"
#include "instructions.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    program pay_to(const bitcoin::pubkey&);
    program pay_to(const bitcoin::uncompressed_pubkey&);
    program redeem_from_pay_to_pubkey(const bitcoin::signature&);
    
    template <typename pubkey>
    struct pay_to_pubkey : public program {
        pubkey Pubkey;
        
        static bool valid(bytes);
        
        bool valid() const {
            return Pubkey.valid();
        }
        
        static pubkey to(const bytes& s) {
            throw data::method::unimplemented{"abstractions::script::pay_to_pubkey::to"};
        }
        
        pubkey to() const {
            return Pubkey;
        }
        
        pay_to_pubkey(pubkey p) : Pubkey{p} {}
        pay_to_pubkey(bytes& b) : Pubkey{to(b)} {}
        
    };
    
    inline program pay_to(const bitcoin::pubkey& p) {
        return program{} << push(p.Pubkey) << check_signature();
    }
    
    inline program pay_to(const bitcoin::uncompressed_pubkey& p) {
        return program{} << push(p.Pubkey) << check_signature();
    }
    
    inline program redeem_from_pay_to_pubkey(const bitcoin::signature& x) {
        return program{} << push(x);
    }
    
}

#endif
