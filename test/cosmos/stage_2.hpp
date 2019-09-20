// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/wallet/spendable.hpp>
#include <abstractions/wallet/wallet.hpp>

namespace abstractions::bitcoin::cosmos::test {
    // thrown for failed tests
    // TODO replace with google test. 
    struct failure {};
    
    // The test goes through several rounds of redeeming 
    // outputs and creating txs. 
    struct step {
        pattern Pattern;
        secret Key;
        secret Change;
    };
    
    using steps = queue<step>;
    
    using funds = redeem::funds<script, txid, secret, pubkey>;
    
    // test whether the tx is valid. This requires the previous
    // outputs that have been redeemed by it. 
    bool valid_scripts(queue<spendable> prevout, const transaction& tx);
    
    wallet round(wallet to_spend, step next);
    
    wallet run(wallet init, queue<step> steps);
    
    struct initial {
        satoshi Amount;
        outpoint Outpoint;
    };
    
    initial make_initial(); // make fake initial input;
    
    struct sequence {
        wallet Init;
        queue<step> Steps;
        
        wallet operator()() const {
            return run(Init, Steps);
        }
        
        static queue<step> initialize(queue<step> x, queue<secret>, pattern) {
            return x;
        }
        
        template <typename... P>
        static queue<step> initialize(queue<step> x, queue<secret> q, pattern a, pattern b, P... patt) {
            return initialize(x.append(
                step{b, q.first(), q.rest().first()}
            ), q.rest().rest(), b, patt...);
        }
        
        template <typename... P>
        sequence(initial init, queue<secret> q, pattern p, P... patt) : 
            Init{wallet{spendable{
                output{init.Amount, p->pay(q.first())}, 
                init.Outpoint, 
                q.first(), p}}},
            Steps{initialize({}, q.rest(), p, patt...)} {}
    };
    
    pattern p = &pay_to_address_compressed;
    //pattern p_a_u = pay_to_address_uncompressed;
    pattern p_p_c = &pay_to_pubkey_compressed;
    //pattern p_p_u = pay_to_pubkey_uncompressed;
    
    // Need at least 5 per test sequence. (one for the first step and two for each subsequent.)
    queue<secret> test_keys();
    
    sequence test_sequence_1{make_initial(), test_keys(), p, p, p};
    //sequence test_sequence_2{make_initial(), test_keys(), &p, &p_a_u, &p};
    //sequence test_sequence_3{make_initial(), test_keys(), p, p_p_c, p};
    //sequence test_sequence_4{make_initial(), test_keys(), &p, &p_p_u, &p};
    
}

#endif 

