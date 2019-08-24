// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/pattern.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/wallet/spendable.hpp>
#include <data/fold.hpp>
#include "stage_1.hpp"

namespace abstractions::bitcoin::cosmos::test {
    
    struct step {
        secret Key;
        pattern& Pattern;
    };
    
    using steps = queue<step>;
    
    steps thread(queue<secret> k, queue<pattern&> p) {
        if (p.empty() || k.empty()) return {};
        return steps{{step{k.first(), p.first()}}}.append(thread(k.rest(), p.rest()));
    }
    
    satoshi expected_cost(vertex v);
    
    bool valid_scripts(vector<spendable> prevout, const transaction& tx);
    
    bool reasonable_fee(const transaction& tx); 
    
    bool test_tx(vector<spendable> prevout, const transaction& tx);
    
    spendable round(spendable spend, step next);
    
    spendable run(spendable init, queue<step> steps) {
        return data::fold(&round, init, steps);
    }
    
    struct initial {
        satoshi Amount;
        outpoint Outpoint;
    };
    
    initial make_initial(); // make fake initial input;
    
    struct sequence {
        spendable Init;
        queue<step> Steps;
        
        spendable operator()() const {
            return run(Init, Steps);
        }
        
        sequence(queue<pattern&> p, queue<secret> k, initial i) : 
            Init{k.first(),
                output{i.Amount, p.first().pay(k.first())}, 
                i.Outpoint,
                static_cast<redeemer&>(p.first())}, 
            Steps{thread(k.rest(), p.rest())} {}
    };
    
    const pattern& p = pay_to_address_compressed;
    const pattern& p_a_u = pay_to_address_uncompressed;
    const pattern& p_p_c = pay_to_pubkey_compressed;
    const pattern& p_p_u = pay_to_pubkey_uncompressed;
    
    list<queue<pattern&>> test_data{{p, p, p}, {p, p_a_u, p}, {p, p_p_c, p}, {p, p_p_u, p}};
    
}

#endif 

