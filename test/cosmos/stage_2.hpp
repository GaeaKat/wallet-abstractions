// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/pattern.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/wallet/spendable.hpp>

namespace abstractions::bitcoin::test {
    
    struct test_step {
        secret Key;
        pattern& Pattern;
    };
    
    spendable tx_test(spendable input, test_step next); // TODO
    
}

#endif 
