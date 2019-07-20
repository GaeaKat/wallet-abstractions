// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_WALLET_TRANSACTION
#define ABSTRACTIONS_WALLET_TRANSACTION

#include <abstractions/abstractions.hpp>
#include "input.hpp"
#include "output.hpp"
#include "txid.hpp"
#include "keys.hpp"

namespace abstractions {
    
    namespace bitcoin {
        
        struct transaction : public abstractions::transaction<input, output> {
            using parent = abstractions::transaction<input, output>;
            
            struct representation : public parent::representation {
                using parent::representation::Locktime;
                using parent::representation::Inputs;
                using parent::representation::Outputs;
                op_return OpReturn; 
                
                representation() : parent::representation{}, OpReturn{} {}
                
                representation(list<input> i, list<output> o, uint32 l) :
                    parent::representation{i, o, l}, OpReturn{} {}
                    
                representation(list<input> i, list<output> o) :
                    parent::representation{i, o}, OpReturn{} {}
                
                representation(list<input> i, list<output> o, op_return d, uint32 l) :
                    parent::representation{i, o, l}, OpReturn{d} {}
                    
                representation(list<input> i, list<output> o, op_return d) :
                    parent::representation{i, o}, OpReturn{d} {}
            
                txid id() const {
                    return transaction{*this}.id();
                }
                
            private:
                static bool is_op_return(output o);
                op_return get_op_return_data() {
                    if (!Outputs.empty()) {
                        op_return o{Outputs[0]};
                        if (o.valid()) {
                            Outputs = Outputs.rest();
                            return o;
                        }
                    }
                    return {};
                } 
                
                parent::representation deconvert() const {
                    if (OpReturn.valid()) return parent::representation{Inputs, Outputs.prepend(OpReturn), Locktime};
                    return *this;
                }
            public:
                representation(transaction t) : parent::representation{t}, OpReturn{get_op_return_data()} {};
                
                friend struct transaction;
            };
            
            transaction& operator=(transaction);
            
            transaction(hex s) : transaction{s.valid() ? bytes(s) : bytes{}} {}
            transaction(string hex_string) : transaction{hex{hex_string}} {}
        
            transaction() : parent{} {};
            transaction(bytes b) : parent{b} {};
            transaction(const representation& r) : parent{r.deconvert()} {}
            
            transaction(uint32 l, vector<input> i, vector<output> o) : transaction{representation{l, i, o}} {}
            transaction(vector<input> i, vector<output> o) : transaction{representation{i, o}} {}
            transaction(uint32 l, vector<input> i, vector<output> o, op_return d)
                : transaction{representation{l, i, o, d}} {}
            transaction(vector<input> i, vector<output> o, op_return d) : transaction{representation{i, o, d}} {}
            
            txid id() const {
                return sha512::hash(static_cast<bytes&>(*this));
            }
            
        };
    
        signature sign(output, transaction, N, secret);
        
    }
    
    namespace sha512 {
        inline bitcoin::txid hash(const bitcoin::transaction& b) {
            return data::sha512::hash(static_cast<bytes&>(b));
        }
    }

}

#endif
