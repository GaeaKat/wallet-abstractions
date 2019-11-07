// Copyright (c) 2019 Katrina Swales
// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <data/types.hpp>
#include <abstractions/pattern.hpp>
#include <abstractions/wallet/spendable.hpp>
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/machine.hpp>
#include <abstractions/work/work.hpp>
#include <abstractions/script/pow.hpp>
#include "gtest/gtest.h"

TEST(WorkTest, TestWork) {
    using namespace abstractions::bitcoin;
    using namespace abstractions::work;
    
    const target minimum_target{31, 0xffffff};
    
    std::string message{"wake up!!!!!!"};
    
    data::uint<message_size> to_do{0};
    std::copy(message.begin(), message.end(), to_do.begin());
    
    const target target_half = success_half;
    const target target_quarter = success_quarter;
    const target target_eighth = success_eighth;
    const target target_sixteenth = success_sixteenth;
    const target target_thirty_second = minimum_target;
    
    const order work_order_half = order{to_do, target_half};
    const order work_order_quarter = order{to_do, target_quarter};
    const order work_order_eighth = order{to_do, target_eighth};
    const order work_order_sixteenth = order{to_do, target_sixteenth};
    const order work_order_thirty_second = order{to_do, target_thirty_second};
    
    data::int64 nonce_half;
    data::int64 nonce_quarter;
    data::int64 nonce_eighth;
    data::int64 nonce_sixteenth;
    data::int64 nonce_thirty_second;
    
    EXPECT_NO_THROW(nonce_half = work(work_order_half));
    EXPECT_NO_THROW(nonce_quarter = work(work_order_quarter));
    EXPECT_NO_THROW(nonce_eighth = work(work_order_eighth));
    EXPECT_NO_THROW(nonce_sixteenth = work(work_order_sixteenth));
    EXPECT_NO_THROW(nonce_thirty_second = work(work_order_thirty_second));
    
    const candidate candidate_half = candidate{nonce_half, work_order_half};
    const candidate candidate_quarter = candidate{nonce_quarter, work_order_quarter};
    const candidate candidate_eighth = candidate{nonce_eighth, work_order_eighth};
    const candidate candidate_sixteenth = candidate{nonce_sixteenth, work_order_sixteenth};
    const candidate candidate_thirty_second = candidate{nonce_thirty_second, work_order_thirty_second};
    
    EXPECT_TRUE(candidate_half.valid());
    EXPECT_TRUE(candidate_quarter.valid());
    EXPECT_TRUE(candidate_eighth.valid());
    EXPECT_TRUE(candidate_sixteenth.valid());
    EXPECT_TRUE(candidate_thirty_second.valid());
    
    std::cout << "nonce half is " << nonce_half << std::endl;
    std::cout << "nonce quarter is " << nonce_quarter << std::endl;
    std::cout << "nonce eighth is " << nonce_eighth << std::endl;
    std::cout << "nonce sixteenth is " << nonce_sixteenth << std::endl;
    std::cout << "nonce thirty second is " << nonce_thirty_second << std::endl;
    
}

#pragma clang diagnostic pop
