// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_PAYMENT
#define ABSTRACTIONS_WALLET_PAYMENT

#include "keys.hpp"
#include "address.hpp"
#include "spendable.hpp"
#include <abstractions/script/pay_to_address.hpp>

namespace abstractions::bitcoin {
    struct payment {
        satoshi Value;
        payment(satoshi v) : Value{v} {}
        payment() : Value{0} {}
        
        virtual script order() const = 0;
        
        output pay() const {
            return output{Value, order()};
        }
    };
    
    struct to_script final : public payment {
        script Script;
        
        to_script(satoshi v, script s) : payment{v}, Script{s} {}
        to_script(output o) : payment{o.Value}, Script{o.ScriptPubKey} {}
        
        script order() const final override {
            return Script;
        };
    };
    
    struct to_pattern final : public payment {
        payable Pattern;
        secret Key;
        
        to_pattern(satoshi v, payable p, secret k) : payment{v}, Pattern{p}, Key{k} {}
        
        script order() const final override {
            return Pattern.pay(Key);
        };
    };
    
    struct to_address final : public payment {
        address Address;
        
        to_address(satoshi v, address a) : payment{v}, Address{a} {}
        
        script order() const final override {
            return abstractions::script::pay_to(Address)->compile();
        };
    };
}

#endif
