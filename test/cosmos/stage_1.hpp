// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef TEST_COSMOS_STAGE_1
#define TEST_COSMOS_STAGE_1

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>

namespace abstractions::bitcoin::test {
    struct stage_1 {
        string SecretWIF;
        string SecretWIFCompressed;
        string PubkeyHex;
        string PubkeyWIF;
        string PubkeyWIFCompressed;
        string AddressBase58;
        string AddressCashaddr;
        
        bool run() {
            secret s_wif{SecretWIF};
            if (!s_wif.valid()) return false;
            secret s_wif_compressed{SecretWIFCompressed};
            if (!s_wif_compressed.valid()) return false;
            if (s_wif != s_wif_compressed) return false;
            
            pubkey p_hex{PubkeyHex};
            if (!p_hex.valid()) return false;
            pubkey p_wif{PubkeyWIF};
            if (!p_wif.valid()) return false;
            pubkey p_wif_compressed{PubkeyWIFCompressed};
            if (!p_wif_compressed.valid()) return false;
            if (p_hex != p_wif) return false;
            if (p_wif != p_wif_compressed) return false;
            
            address a_base58{AddressBase58};
            if (!a_base58.valid()) return false;
            address a_cashaddr{AddressCashaddr};
            if (!a_cashaddr.valid()) return false;
            if (a_base58 != a_cashaddr) return false;
            
            if (s_wif.to_public() != p_hex) return false;
            if (p_hex.address() != a_base58) return false;
            
            if (s_wif.encode() != SecretWIF) return false;
            if (p_hex.encode() != PubkeyWIF) return false;
            
            if (a_base58.encode() != AddressBase58) return false;
        }
    };
    
    // TODO fill in some test cases. (4 are good);
    vector<stage_1> stage_1_test_cases{};
}

#endif 
