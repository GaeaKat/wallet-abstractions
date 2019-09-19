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
    
    // used to redeem previous output. 
    struct previous {
        redeemer Pattern;
        secret Key;
        
        script redeem(output prevout, transaction next) const;;
    };
    
    // used to create next output. 
    struct next {
        payable Pattern;
        secret Key;
    };
    
    // The test goes through several rounds of redeeming 
    // outputs and creating txs. 
    struct step {
        previous Previous;
        next next;
    };
    
    using steps = queue<step>;
    
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
        
        sequence(initial i, queue<step> s);
        
    };
    
    auto p = pay_to_address_compressed;
    auto p_a_u = pay_to_address_uncompressed;
    auto p_p_c = pay_to_pubkey_compressed;
    auto p_p_u = pay_to_pubkey_uncompressed;
    
    // Need at least 6
    queue<secret> test_keys();
    
    sequence test_sequence_1{make_initial(), thread{}(test_keys(), &p, &p, &p)};
    sequence test_sequence_2{make_initial(), thread{}(test_keys(), &p, &p_a_u, &p)};
    sequence test_sequence_3{make_initial(), thread{}(test_keys(), &p, &p_p_c, &p)};
    sequence test_sequence_4{make_initial(), thread{}(test_keys(), &p, &p_p_u, &p)};
    
}

#endif 

