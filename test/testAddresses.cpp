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
#include "gtest/gtest.h"
#include "testData.h"

class AddressTest : public testing::TestWithParam<test_data> {};

TEST_P(AddressTest, TestAddresses) {
    using namespace abstractions::bitcoin;
    
    const auto pay_to_address_compressed =
        abstractions::pattern::pay_to_address<secret, pubkey, address, abstractions::bytes>{};
    const auto pay_to_address_uncompressed =
        abstractions::pattern::pay_to_address<secret, uncompressed_pubkey, address, abstractions::bytes>{};
    const auto pay_to_pubkey_compressed =
        abstractions::pattern::pay_to_pubkey<secret, pubkey, abstractions::bytes>{};
    const auto pay_to_pubkey_uncompressed = 
        abstractions::pattern::pay_to_pubkey<secret, uncompressed_pubkey, abstractions::bytes>{};
    
    std::string arbitrary{"It's not easy being green."};
    abstractions::bytes tx{static_cast<unsigned char>(arbitrary.size())};
    std::copy(arbitrary.begin(), arbitrary.end(), tx.begin());
    abstractions::satoshi to_be_redeemed = 2000000000000000;
    abstractions::uint32 index = 3;
    
    secret key{"0x00000000000000000000000000000000000000000000000000000000000101a7"};
    
    pubkey pubkey_compressed = key.to_public();
    uncompressed_pubkey pubkey_uncompressed = key.to_public_uncompressed();
    
    script script_pay_to_pubkey_compressed = pay_to_pubkey_compressed.pay(pubkey_compressed);
    script script_pay_to_pubkey_uncompressed = pay_to_pubkey_uncompressed.pay(pubkey_uncompressed);
    
    script redeem_pay_to_pubkey_compressed = pay_to_pubkey_compressed.redeem(
        output{to_be_redeemed, script_pay_to_pubkey_compressed}, 
        abstractions::input_index<abstractions::bytes>{tx, index}, key);
    
    script redeem_pay_to_pubkey_uncompressed = pay_to_pubkey_uncompressed.redeem(
        output{to_be_redeemed, script_pay_to_pubkey_uncompressed}, 
        abstractions::input_index<abstractions::bytes>{tx, index}, key);
    
    address address_compressed = pubkey_compressed.address();
    address address_uncompressed = pubkey_uncompressed.address();
    
    script script_pay_to_address_compressed = pay_to_address_compressed.pay(address_compressed);
    script script_pay_to_address_uncompressed = pay_to_address_uncompressed.pay(address_uncompressed);
    
    script redeem_pay_to_address_compressed = pay_to_address_compressed.redeem(
        output{to_be_redeemed, script_pay_to_address_compressed}, 
        abstractions::input_index<abstractions::bytes>{tx, index}, key);
    
    script redeem_pay_to_address_uncompressed = pay_to_address_uncompressed.redeem(
        output{to_be_redeemed, script_pay_to_address_uncompressed}, 
        abstractions::input_index<abstractions::bytes>{tx, index}, key);
    
    machine m{tx, index, to_be_redeemed};
    
    EXPECT_TRUE(m.run(script_pay_to_pubkey_compressed, redeem_pay_to_pubkey_compressed));
    EXPECT_TRUE(m.run(script_pay_to_pubkey_uncompressed, redeem_pay_to_pubkey_uncompressed));
    EXPECT_TRUE(m.run(script_pay_to_address_compressed, redeem_pay_to_address_compressed));
    EXPECT_TRUE(m.run(script_pay_to_address_uncompressed, redeem_pay_to_address_uncompressed));
    
}

#pragma clang diagnostic pop
