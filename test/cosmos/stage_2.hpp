// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/wallet/spendable.hpp>
#include <abstractions/redeem/funds.hpp>

namespace abstractions::bitcoin::cosmos::test {
    // thrown for failed tests
    // TODO replace with google test. 
    struct failure {};
    
    // list of keys that are used to construct tests. 
    vector<secret> keys();
    
    // The test goes through several rounds of redeeming 
    // outputs and creating txs. 
    struct step {
        secret Key;
        pattern Pattern;
    };
    
    using steps = queue<step>;
    
    struct thread {
        steps operator()(queue<secret> k) {
            return {};
        }
        
        template <typename P, typename ... rest>
        steps operator()(queue<secret> k, P p, rest... r) {
            if (k.empty()) return {};
            return steps::make(step{k.first(), static_cast<pattern>(p)}).append(
                operator()(k.rest(), r...));
        }
    };
    
    // 1 satoshi per byte is the standard rate currently. 
    bool reasonable_fee(const transaction& tx) {
        return tx.fee() >= tx.size();
    }
    
    using funds = redeem::funds<script, txid, secret>;
    
    // Test everything about whether a tx is good. 
    bool test_tx(queue<output> prevout, const transaction& tx);
    
    funds round(funds to_spend, step next);
    
    funds run(funds init, queue<step> steps);
    
    struct initial {
        satoshi Amount;
        outpoint Outpoint;
    };
    
    initial make_initial(); // make fake initial input;
    
    funds make_initial_funds(initial, step); 
    
    struct sequence {
        funds Init;
        queue<step> Steps;
        
        funds operator()() const {
            return run(Init, Steps);
        }
        
        sequence(initial i, queue<step> s) : Init{make_initial_funds(i, s.first())}, Steps{s.rest()} {}
        
    };
    
    auto p = pay_to_address_compressed;
    auto p_a_u = pay_to_address_uncompressed;
    auto p_p_c = pay_to_pubkey_compressed;
    auto p_p_u = pay_to_pubkey_uncompressed;
    
    queue<secret> test_keys();
    
    sequence test_sequence_1{make_initial(), thread{}(test_keys(), &p, &p, &p)};
    sequence test_sequence_2{make_initial(), thread{}(test_keys(), &p, &p_a_u, &p)};
    sequence test_sequence_3{make_initial(), thread{}(test_keys(), &p, &p_p_c, &p)};
    sequence test_sequence_4{make_initial(), thread{}(test_keys(), &p, &p_p_u, &p)};
    
}

#endif 

