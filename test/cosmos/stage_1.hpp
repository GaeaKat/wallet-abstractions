// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_1
#define TEST_COSMOS_STAGE_1

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>
#include <data/for_each.hpp>

#include "gtest/gtest.h"

namespace abstractions::bitcoin::test {
    struct failure {};
    
    class one {
        secret SecretWIF;
        secret SecretWIFUncompressed;
        pubkey PubkeyHex;
        pubkey PubkeyHexUncompressed;
        address AddressBase58;
        address AddressCashaddr;
    public:
        one(string secret_wif, 
            string secret_wif_uncompressed, 
            string pubkey_hex, 
            string pubkey_hex_uncompressed,
            string addr_58,
            string cashaddr) : 
            SecretWIF{secret_wif}, 
            SecretWIFUncompressed{secret_wif_uncompressed},
            PubkeyHex{pubkey_hex},
            PubkeyHexUncompressed{pubkey_hex_uncompressed}, 
            AddressBase58{addr_58}, 
            AddressCashaddr{cashaddr} {
            
            if (!SecretWIF.valid()) throw failure{};
            if (!SecretWIFUncompressed.valid()) throw failure{};
            if (!PubkeyHex.valid()) throw failure{};
            if (!PubkeyHexUncompressed.valid()) throw failure{};
            if (!AddressBase58.valid()) throw failure{};
            if (!AddressCashaddr.valid()) throw failure{};
            
            if (SecretWIF != SecretWIFUncompressed) throw failure{};
            if (PubkeyHex != PubkeyHexUncompressed) throw failure{};
            if (AddressBase58 != AddressCashaddr) throw failure{};
            
            if (SecretWIF.to_public() != PubkeyHex) throw failure{};
            if (PubkeyHex.address() != AddressBase58) throw failure{};
            
            if (SecretWIF.encode() != secret_wif) throw failure{};
            if (PubkeyHex.encode() != pubkey_hex) throw failure{};
            if (AddressBase58.encode() != addr_58) throw failure{};
        }
        
        secret key() const {
            return SecretWIF;
        }
        
        static vector<one> cases() {
            // generated with bitaddress.org and cashaddress.org
            return {
                one{"L2rW8amvjR19iSZ1wVU9keXBqEjQ9fMSCw9bsSKSmSCXTxqfz2Bn",
                    "5K6KqPc6q8FXyWogBXvH2jV8tiB4S5AALUDpmxadei44jTV6p4S",
                    "02DE7A990579BCA352633D340F05E7E7158661B0DCA0BA40A5AB5E0328A312216F",
                    "04DE7A990579BCA352633D340F05E7E7158661B0DCA0BA40A5AB5E0328A312216FF40F50C2B6E03D863B19B9B679787FB75634F8BD00C2F2400196999CC9AB8E76", 
                    "1AWfki61q1phyV1SA6Ytp38c9Ft5kipwV8",
                    "qp59tzmez92uts6y8pk72ax0dvee6an9agq3wk4zkh"}, 
                one{"KzmVx4hyCB6GAQoxMQae8GnokPG2hrJCP6Z7EjZS9MJZhf7pbpmW",
                    "5Jcun6poGDi4tXKLnrkRGhHGaPiU7zPUW2FyhGXupf8c3xFKwA5",
                    "023EA79C33BC21008356CA4C0E06A896014D94AD5216F54C44A3A94E1C8B39B1B1", 
                    "043EA79C33BC21008356CA4C0E06A896014D94AD5216F54C44A3A94E1C8B39B1B1F252B4B35D4CA96B8C6D7601A75D36F06BDB333B0E4F0C13C5E4004E49C5FE2A",
                    "1DKsEVtWQ6QGWBQ32fVDuCYQasxawApdqm", 
                    "qzrn9mwtv7hm8ezuanh3wk78wumtflc9msjqmh7pu4"}, 
                one{"L2HMpTWtyCdQkhL1tTQDSP4ssw7DVazacTBEzkAv1DSi8jjask6a",
                    "5JxpK17mrSHrnhQLgkbG42q1CYHpEj94Y9CPCixGBUHhb32UErf",
                    "03F063CDE7542B8FA3BC55739B44DA63B38AEE8583CD9E3C351D0BB2F5968D6805",
                    "04F063CDE7542B8FA3BC55739B44DA63B38AEE8583CD9E3C351D0BB2F5968D6805BBB8F5C9ACEBB8DA15610B68DE0B2EE6441BD54D1893E06618C8E320010DCA17", 
                    "13GYJRir1xn5cyVWqLzQPaiZr9BLJdfKAv", 
                    "qqvwp852xycjuf5erjyq0d7rnvyc0vsj0vjrmn0rpw"}, 
                one{"L1vXPxhPFAe5taRGcmxcUuKKmmnbV1Q59TazBTFwHsVugRhQbGJU",
                    "5Jt6XaTpdjxyqqojWQKwiDJkDs2GWuerRaDEQfaHqEFhwGeMMo3",
                    "035A5CA5E685803CB8CD54198F3CFD71187F85F940EAECCE0D5D6551911306738C", 
                    "045A5CA5E685803CB8CD54198F3CFD71187F85F940EAECCE0D5D6551911306738C636205F2C171613EBDA6A345D1078D359B985C829B6E4715BC93BBEDD4E7740B",
                    "1DXj3zwApeKaSCyEZD5Pjkzai8p5XmwxzY",
                    "qzyhz96ud6hz40mmzw4nlgv5f7pk7dzxnqe9dp23lh"
                }
            };
        }
        
    };
    
    vector<secret> keys() {
        vector<one> cases = one::cases();
        uint size = cases.size();
        std::vector<secret> keys{size};
        for (uint i = 0; i < 0; i++) {
            keys[i] = cases[i].key();
        }
        return keys;
    }
    
}

#endif 
