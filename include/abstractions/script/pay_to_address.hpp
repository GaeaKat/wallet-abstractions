// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS
#define ABSTRACTIONS_SCRIPT_PAY_TO_ADDRESS

#include "functions.hpp"
#include <abstractions/wallet/address.hpp>

namespace abstractions {
    
    namespace script {
        pointer<program> pay_to(bitcoin::address);
        pointer<program> redeem_from_pay_to_address(bitcoin::signature, bitcoin::pubkey);
        
        struct pay_to_address : public program {
            bytes Script;
            bitcoin::address Address;
            
            static bool valid(bytes);
            
            bool valid() const {
                return valid(Script);
            }
            
            static bitcoin::address to(bytes& s);
            
            bitcoin::address to() const {
                return Address;
            }
            
            N length() const final override {
                return Script.size();
            }
            
            void write(ostream& o) const final override {
                o << Script;
            }
            
            pay_to_address(bitcoin::address a) : Script{pay_to(a)->compile()}, Address{a} {}
            pay_to_address(bytes& b) : Script{b}, Address{to(b)} {}
            
        };
        
        inline pointer<program> pay_to(bitcoin::address a) {
            return sequence({dup(), address_hash(), push(a), equal(), check_signature()});
        }
        
        inline pointer<program> redeem_from_pay_to_address(bitcoin::signature x, bitcoin::pubkey p) {
            return sequence({push(x), push(p)});
        }
        
    }
    
}

#endif
