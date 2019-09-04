// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef WALLET_ABSTRACTIONS_TESTSTAGE1_H
#define WALLET_ABSTRACTIONS_TESTSTAGE1_H
#include <data/types.hpp>
#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>
#include "gtest/gtest.h"
#include "testData.h"


class Stage1Test : public testing::TestWithParam<test_data> {
public:
    abstractions::bitcoin::secret SecretWIF;
    abstractions::bitcoin::secret SecretWIFUncompressed;
    abstractions::bitcoin::pubkey PubkeyHex;
    abstractions::bitcoin::uncompressed_pubkey PubkeyHexUncompressed;
    abstractions::bitcoin::address AddressBase58;
    abstractions::bitcoin::address AddressCashaddr;
protected:
    void SetUp() override {
        SecretWIF = abstractions::bitcoin::secret(GetParam().secret_wif);
        SecretWIFUncompressed = abstractions::bitcoin::secret(GetParam().secret_wif_uncompressed);
        PubkeyHex = abstractions::bitcoin::pubkey(GetParam().pubkey_hex);
        PubkeyHexUncompressed = abstractions::bitcoin::uncompressed_pubkey(GetParam().pubkey_hex_uncompressed);
        AddressBase58=abstractions::bitcoin::address(GetParam().addr_58);
        AddressCashaddr = abstractions::bitcoin::address(abstractions::bitcoin::cashaddr::read(GetParam().cashaddr));
    }

};

class Stage1InvalidTest : public testing::TestWithParam<test_data> {
public:
    abstractions::bitcoin::secret SecretWIF;
    abstractions::bitcoin::secret SecretWIFUncompressed;
    abstractions::bitcoin::pubkey PubkeyHex;
    abstractions::bitcoin::uncompressed_pubkey PubkeyHexUncompressed;
    abstractions::bitcoin::address AddressBase58;
    abstractions::bitcoin::address AddressCashaddr;
protected:
    void SetUp() override {
        SecretWIF = abstractions::bitcoin::secret(GetParam().secret_wif);
        SecretWIFUncompressed = abstractions::bitcoin::secret(GetParam().secret_wif_uncompressed);
        PubkeyHex = abstractions::bitcoin::pubkey(GetParam().pubkey_hex);
        PubkeyHexUncompressed = abstractions::bitcoin::uncompressed_pubkey(GetParam().pubkey_hex_uncompressed);
        AddressBase58=abstractions::bitcoin::address(GetParam().addr_58);
        AddressCashaddr = abstractions::bitcoin::address(abstractions::bitcoin::cashaddr::read(GetParam().cashaddr));
    }

};


#endif //WALLET_ABSTRACTIONS_TESTSTAGE1_H
