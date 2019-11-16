// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS
#define ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS

#include "functions.hpp"
#include "push.hpp"
#include "instructions.hpp"
#include <abstractions/wallet/address.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    program pay_to(const bitcoin::address&);
    program redeem_from_pay_to_address(const bitcoin::signature&, const bitcoin::pubkey&);
    program redeem_from_pay_to_address(const bitcoin::signature&, const bitcoin::uncompressed_pubkey&);
    
    struct pay_to_address {
        bitcoin::address Address;
        
        static bitcoin::address to(bytes_view s) {
            throw data::method::unimplemented{"abstractions::script::pay_to_address::to"};
        }
        
        pay_to_address(bitcoin::address a) : Address{a} {}
        pay_to_address(bytes_view b) : Address{to(b)} {}
        
        static bool valid(bytes);
        
        bool valid() const {
            return Address.valid();
        }
        
        bitcoin::address to() const {
            return Address;
        }
        
    };
    
    inline program pay_to(const bitcoin::address& a) {
        return program{} + dup() + address_hash() + push(a.Digest) + equal_verify() + check_signature();
    }
    
    inline program redeem_from_pay_to_address(const bitcoin::signature& x, const bitcoin::pubkey& p) {
        return program{} + push(x) + push(p.Pubkey);
    }
    
    inline program redeem_from_pay_to_address(const bitcoin::signature& x, const bitcoin::uncompressed_pubkey& p) {
        return program{} + push(x) + push(p.Pubkey);
    }
    
}

#endif
