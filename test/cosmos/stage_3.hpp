// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_3
#define TEST_COSMOS_STAGE_3

#include <abstractions/work/work.hpp>
#include <abstractions/script/pow.hpp>
#include "stage_2.hpp"

namespace abstractions::bitcoin::cosmos::test {
    static const work::target minimum_target{31, 0x00ffffff};
    
    struct lock_pow final : pattern {
        work::order Order;
        
        lock_pow(work::order o) : Order{o.Target < minimum_target ? work::order{} : o} {}
        
        bool valid() const {
            return Order.valid() && Order.Target < minimum_target;
        }
        
        // we don't really use the key. 
        const script pay(const secret&) const final override {
            return abstractions::script::lock_by_pow(Order.Reference, Order.Target)->compile();
        }
        
        const script redeem(satoshi amount, const script s, const abstractions::transaction<input, output>& t, index i, const secret& k) const final override {
            if (Order.Target < minimum_target) throw failure{};
            work::candidate candidate = work::work(Order);
            return abstractions::script::unlock_with_pow(
                bitcoin::sign(bitcoin::output{amount, s}, t, i, k), 
                k.to_public(),
                data::endian::halves<uint32, uint64, data::endian::order::big>::combine(
                    candidate.version(), 
                    candidate.nonce()))->compile();
        } 
        
    };
    
    const lock_pow lock_pow_pattern{work::order{/* arbitrary test data here */, minimum_target}};
    
    const pattern& l_p = lock_pow_pattern;
    
}

#endif 

