// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/pattern.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/wallet/spendable.hpp>
#include "stage_1.hpp"

namespace abstractions::bitcoin::cosmos::test {
    
    struct step {
        secret Key;
        pattern& Pattern;
    };
    
    satoshi expected_cost(vertex v);
    
    bool valid_scripts(vector<spendable> prevout, const transaction& tx);
    
    bool reasonable_fee(const transaction& tx); 
    
    bool test_tx(vector<spendable> prevout, const transaction& tx);
    
    spendable round(spendable spend, step next);
    
}

#endif 
