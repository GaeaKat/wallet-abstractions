// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_3
#define TEST_COSMOS_STAGE_3

#include "stage_2.hpp"
#include <abstractions/work/work.hpp>

namespace abstractions::bitcoin::cosmos::test {
    struct lock_pow final : public pattern {
        work::order Order;
        
        // make a script pubkey. 
        const script pay(const secret&) const final override;
        
        // make a script signature.
        const script redeem(satoshi, const script, const abstractions::transaction<input, output>&, index, const secret&) const final override;
    };
    
}

#endif 

