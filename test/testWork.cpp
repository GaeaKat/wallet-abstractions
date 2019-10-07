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
#include "testData.h"

class AddressTest : public testing::TestWithParam<test_data> {};

TEST_P(AddressTest, TestAddresses) {
    using namespace abstractions::bitcoin;
    using namespace abstractions::work;
    
    const target     minimum_target{31, 0xffffff};
    
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
    
    const candidate candidate_half = work(work_order_half);
    const candidate candidate_quarter = work(work_order_quarter);
    const candidate candidate_eighth = work(work_order_eighth);
    const candidate candidate_sixteenth = work(work_order_sixteenth);
    const candidate candidate_thirty_second = work(work_order_thirty_second);
    
    const data::sha256::digest digest_half = candidate_half.hash();
    const data::sha256::digest digest_quarter = candidate_quarter.hash();
    const data::sha256::digest digest_eighth = candidate_eighth.hash();
    const data::sha256::digest digest_sixteenth = candidate_sixteenth.hash();
    const data::sha256::digest digest_thirty_second = candidate_thirty_second.hash();
    
    EXPECT_TRUE(digest_half < target_half.expand());
    EXPECT_TRUE(digest_quarter < target_half.expand());
    EXPECT_TRUE(digest_eighth < target_eighth.expand());
    EXPECT_TRUE(digest_sixteenth < target_sixteenth.expand());
    EXPECT_TRUE(digest_thirty_second < target_thirty_second.expand());
    
    const data::uint64 nonce_half = candidate_half.extended_nonce();
    const data::uint64 nonce_quarter = candidate_quarter.extended_nonce();
    const data::uint64 nonce_eighth = candidate_eighth.extended_nonce();
    const data::uint64 nonce_sixteenth = candidate_sixteenth.extended_nonce();
    const data::uint64 nonce_thirty_second = candidate_thirty_second.extended_nonce();
    
    std::cout << "nonce half is " << nonce_half << std::endl;
    std::cout << "nonce quarter is " << nonce_quarter << std::endl;
    std::cout << "nonce eighth is " << nonce_eighth << std::endl;
    std::cout << "nonce sixteenth is " << nonce_sixteenth << std::endl;
    std::cout << "nonce thirty second is " << nonce_thirty_second << std::endl;
    
}

#pragma clang diagnostic pop
