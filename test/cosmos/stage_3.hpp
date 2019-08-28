// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_3
#define TEST_COSMOS_STAGE_3

#include <abstractions/work/work.hpp>
#include <abstractions/script/pow.hpp>
#include "stage_2.hpp"

namespace abstractions::bitcoin::cosmos::test {
    static const work::target     minimum_target{31, 0xffffff};
    
    static const work::target       success_half{32, 0x800000};
    static const work::target    success_quarter{32, 0x400000};
    static const work::target     success_eighth{32, 0x200000};
    static const work::target  success_sixteenth{32, 0x100000};
    
    struct lock_pow final : public abstractions::pattern::abstract::pattern<secret, script,
        abstractions::transaction<input, output>> {
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
            // Get number of trials and check that it is reasonable. 
            return abstractions::script::unlock_with_pow(
                bitcoin::sign(bitcoin::output{amount, s}, t, i, k), 
                k.to_public(),
                data::endian::halves<uint32, uint64, data::endian::order::big>::combine(
                    candidate.version(), 
                    candidate.nonce()))->compile();
        } 
        
    };
    
    const lock_pow lock_pow_pattern_02{work::order{{}, {}, success_half}};
    const lock_pow lock_pow_pattern_04{work::order{{}, {}, success_quarter}};
    const lock_pow lock_pow_pattern_08{work::order{{}, {}, success_eighth}};
    const lock_pow lock_pow_pattern_16{work::order{{}, {}, success_sixteenth}};
    
    list<queue<pattern>> test_data_3{
        list<pattern>::make(&p, &lock_pow_pattern_02, &p), 
        list<pattern>::make(&p, &lock_pow_pattern_04, &p), 
        list<pattern>::make(&p, &lock_pow_pattern_08, &p), 
        list<pattern>::make(&p, &lock_pow_pattern_16, &p)};
    
}

#endif 

