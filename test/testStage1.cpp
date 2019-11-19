// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <data/types.hpp>
#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>
#include "gtest/gtest.h"
#include "testStage1.h"


TEST_P(Stage1Test, WIF) {
    EXPECT_TRUE(this->SecretWIF.valid()) << "Secret WIF is not valid";
    EXPECT_TRUE(this->SecretWIFUncompressed.valid()) << "Uncompressed Secret Wif is not valid";
    EXPECT_EQ(this->SecretWIF, this->SecretWIFUncompressed) << "Can't get public key from compressed secret";
}

TEST_P(Stage1Test, PubHexValid) {
    EXPECT_TRUE(this->PubkeyHex.valid()) << "Public Key is not valid";
    EXPECT_TRUE(this->PubkeyHexUncompressed.valid()) << "Uncompressed Public Key is not valid";
    EXPECT_EQ(this->SecretWIF.to_public(), PubkeyHex) << "Can't get compressed public key from secret";
    EXPECT_EQ(this->SecretWIFUncompressed.to_public_uncompressed(), PubkeyHexUncompressed) << "Can't get uncompressed public key from secret";
    //EXPECT_TRUE(this->PubkeyHexUncompressed.compress() == this->PubkeyHex)
}

TEST_P(Stage1Test, Addr58Valid) {
    EXPECT_TRUE(this->AddressBase58.valid()) << "Address in base 58 is not valid";
}

TEST_P(Stage1Test, DISABLED_CashValid) {
    EXPECT_TRUE(this->AddressCashaddr.valid()) << "Address in Cash is not valid";
}

TEST_P(Stage1Test, SecretWIFDecompression) {
    EXPECT_EQ(this->SecretWIF, this->SecretWIFUncompressed) << "Secret Wif not equal to it's decompressed version";
}

TEST_P(Stage1Test, DISABLED_AddressFormatComparison) {
    std::cout << "base58: " << this->AddressBase58.write() << std::endl;
    std::cout << "cashaddr: " << this->AddressCashaddr.write() << std::endl;


    std::cout << "base58 as cash: " <<abstractions::bitcoin::cashaddr::write(this->AddressBase58) << std::endl;
    std::cout << "cashaddr as cash: " << abstractions::bitcoin::cashaddr::write(this->AddressCashaddr) << std::endl;
    EXPECT_EQ(this->AddressCashaddr, this->AddressBase58) << "CashAddr doesn't equal traditional format";
}

TEST_P(Stage1Test, GetAddressFromPublicKey) {
    EXPECT_EQ(this->PubkeyHex.address(), this->AddressBase58) << "Can't get address from public key";
}

// This test fails. 
TEST_P(Stage1Test, WriteSecretWIF) {
    EXPECT_EQ(this->SecretWIF.write(), GetParam().secret_wif) << "cannot derive wif " << GetParam().secret_wif << " from key " << SecretWIF.Secret.Value;
}

TEST_P(Stage1Test, WritePubKey) {
    EXPECT_EQ(this->PubkeyHex.write(), GetParam().pubkey_hex);
}

TEST_P(Stage1Test, WriteAddress) {
    EXPECT_EQ(this->AddressBase58.write(), GetParam().addr_58);
}

// Invalid Tests

TEST_P(Stage1InvalidTest, SecretWIFInvalid) {
    EXPECT_FALSE(this->SecretWIF.valid()) << "Secret WIF is valid";
}

TEST_P(Stage1InvalidTest, SecretWIFUncompressedInvalid) {
    EXPECT_FALSE(this->SecretWIFUncompressed.valid()) << "Uncompressed Secret Wif is valid";
}

TEST_P(Stage1InvalidTest, PubHexInvalid) {
    EXPECT_FALSE(this->PubkeyHex.valid()) << "Public Key isvalid";
}

TEST_P(Stage1InvalidTest, PubHexUncompressedInvalid) {
    EXPECT_FALSE(this->PubkeyHexUncompressed.valid()) << "Uncompressed Public Key is valid";
}

TEST_P(Stage1InvalidTest, Addr58Invalid) {
    EXPECT_FALSE(this->AddressBase58.valid()) << "Address in base 58 is valid";
}

TEST_P(Stage1InvalidTest, DISABLED_CashInvalid) {
    EXPECT_FALSE(this->AddressCashaddr.valid()) << "Address in Cash is valid";
}


INSTANTIATE_TEST_SUITE_P(Stage1Tests,Stage1Test,testing::ValuesIn(test_dat));
INSTANTIATE_TEST_SUITE_P(Stage1InvalidTests,Stage1InvalidTest,testing::ValuesIn(invalid_test_dat));

#pragma clang diagnostic pop
