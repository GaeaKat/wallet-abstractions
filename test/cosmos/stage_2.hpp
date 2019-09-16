// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/wallet/spendable.hpp>

namespace abstractions::bitcoin::cosmos::test {
    // thrown for failed tests
    // TODO replace with google test. 
    struct failure {};
    
    // list of keys that are used to construct tests. 
    vector<secret> keys();
    
    struct step {
        secret Key;
        pattern Pattern;
    };
    
    using steps = queue<step>;
    
    steps thread(queue<secret> k, queue<pattern> p) {
        if (p.empty() || k.empty()) return {};
        return steps{{step{k.first(), p.first()}}}.append(thread(k.rest(), p.rest()));
    }
    
    satoshi expected_cost(unspent v);
    
    bool valid_scripts(list<output> prevout, const transaction& tx);
    
    bool reasonable_fee(const transaction& tx); 
    
    using funds = redeem::funds<script, txid, secret>;
    
    bool test_tx(funds prevout, const transaction& tx);
    
    spendable round(spendable spend, step next);
    
    spendable run(spendable init, queue<step> steps);
    
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
        
        sequence(queue<pattern> p, queue<secret> k, initial i) : 
            Init{k.first(),
                output{i.Amount, p.first().pay(k.first())}, 
                i.Outpoint,
                static_cast<redeemer>(p.first())}, 
            Steps{thread(k.rest(), p.rest())} {}
    };
    
    pattern p = pay_to_address_compressed;
    pattern p_a_u = pay_to_address_uncompressed;
    pattern p_p_c = pay_to_pubkey_compressed;
    pattern p_p_u = pay_to_pubkey_uncompressed;
    
    list<queue<pattern>> test_data_2{
        list<pattern>::make(&p, &p, &p), 
        list<pattern>::make(&p, &p_a_u, &p), 
        list<pattern>::make(&p, &p_p_c, &p), 
        list<pattern>::make(&p, &p_p_u, &p)};
    
}

#endif 

