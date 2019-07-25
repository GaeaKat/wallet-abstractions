// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_2
#define TEST_COSMOS_STAGE_2

#include <abstractions/pattern.hpp>
#include <abstractions/wallet/transaction.hpp>
#include <abstractions/redeem.hpp>

namespace abstractions::bitcoin::test {
    using redeemer = abstractions::pattern::abstract::pattern<const secret&, const script, const transaction&>;
    using pattern = abstractions::pattern::abstract::pattern<const secret&, const script, const transaction&>;
    
    struct spendable : public vertex<secret, output, outpoint>::spendable {
        redeemer& Redeemer;
        
        script redeem(const transaction& t, index i) const {
            return Redeemer.redeem(Output.Value, Output.ScriptPubKey, t, i, Key);
        };
    };
    
    struct test_step {
        secret Key;
        pattern& Pattern;
    };
    
    spendable tx_test(spendable input, test_step next); // TODO
    
}

#endif 
