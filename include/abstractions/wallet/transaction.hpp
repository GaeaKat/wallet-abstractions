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
        
        const int BSVTxVersion = 2;
        
        struct transaction : public abstractions::transaction<input, output> {
            using parent = abstractions::transaction<input, output>;
            
            struct representation : public parent::representation {
                using parent::representation::Locktime;
                using parent::representation::Inputs;
                using parent::representation::Outputs;
                using parent::representation::Version;
                op_return OpReturn; 
                
                representation() : parent::representation{}, OpReturn{} {}
                
                representation(list<input> i, list<output> o, uint32 l) :
                    parent::representation{i, o, l}, OpReturn{} {}
                    
                representation(list<input> i, list<output> o) :
                    parent::representation{i, o}, OpReturn{} {}
                
                representation(list<input> i, op_return d, list<output> o, uint32 l) :
                    parent::representation{i, o, l}, OpReturn{d} {}
                    
                representation(list<input> i, list<output> o, op_return d) :
                    parent::representation{i, o}, OpReturn{d} {}
            
                txid id() const {
                    return transaction{*this}.id();
                }
                
                bool valid() const {
                    return parent::representation::valid() && Version == BSVTxVersion;
                }
                
            private:
                static bool is_op_return(output o);
                op_return get_op_return_data(); /* {
                    if (!Outputs.empty()) {
                        op_return o{&Outputs.first()};
                        if (o.valid()) {
                            Outputs = Outputs.rest();
                            return o;
                        }
                    }
                    return {};
                } */
                
                parent::representation deconvert() const {
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
            
            transaction(vector<input> i, vector<output> o, uint32 l) : transaction{representation{i, o, l}} {}
            transaction(vector<input> i, vector<output> o) : transaction{representation{i, o}} {}
            transaction(vector<input> i, op_return d, vector<output> o, uint32 l)
                : transaction{representation{i, d, o, l}} {}
            transaction(vector<input> i, vector<output> o, op_return d) : transaction{representation{i, o, d}} {}
            
            txid id() const {
                return abstractions::crypto::hash512(static_cast<bytes&>(*this));
            }
            
        };
        
    }

}

#endif
