// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS
#define ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS

#include "functions.hpp"
#include <abstractions/wallet/address.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    pointer<program> pay_to(const bitcoin::address&);
    pointer<program> redeem_from_pay_to_address(const bitcoin::signature&, const secp256k1::compressed_pubkey&);
    pointer<program> redeem_from_pay_to_address(const bitcoin::signature&, const secp256k1::uncompressed_pubkey&);
    
    struct pay_to_address : public program {
        bytes Script;
        bitcoin::address Address;
        
        static bool valid(bytes);
        
        bool valid() const {
            return valid(Script);
        }
        
        static bitcoin::address to(const bytes& s) {
            throw data::method::unimplemented{};
        }
        
        bitcoin::address to() const {
            return Address;
        }
        
        virtual uint32 length() const final override {
            return Script.size();
        }
        
        virtual void write(writer& o) const final override {
            o << Script;
        }
        
        pay_to_address(bitcoin::address a) : Script{pay_to(a)->compile()}, Address{a} {}
        pay_to_address(bytes& b) : Script{b}, Address{to(b)} {}
        
    };
    
    inline pointer<program> pay_to(const bitcoin::address& a) {
        return sequence({dup(), address_hash(), push(a), equal_verify(), check_signature()});
    }
    
    inline pointer<program> redeem_from_pay_to_address(const bitcoin::signature& x, const secp256k1::compressed_pubkey& p) {
        return sequence({push(x), push(p)});
    }
    
    inline pointer<program> redeem_from_pay_to_address(const bitcoin::signature& x, const secp256k1::uncompressed_pubkey& p) {
        return sequence({push(x), push(p)});
    }
    
}

#endif
