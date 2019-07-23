// Copyright (c) 2017 Pieter Wuille
// Copyright (c) 2017 The Bitcoin developers
// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// Cashaddr is an address format inspired by bech32.
#ifndef ABSTRACTIONS_ABC_CASHADDR
#define ABSTRACTIONS_ABC_CASHADDR

#include <cstdint>
#include <string>
#include <vector>

namespace abc::cashaddr {

    /**
    * Encode a cashaddr string. Returns the empty string in case of failure.
    */
    std::string Encode(const std::string &prefix,
                    const std::vector<uint8_t> &values);

    /**
    * Decode a cashaddr string. Returns (prefix, data). Empty prefix means failure.
    */
    std::pair<std::string, std::vector<uint8_t>>
    Decode(const std::string &str, const std::string &default_prefix);

}

#endif 
