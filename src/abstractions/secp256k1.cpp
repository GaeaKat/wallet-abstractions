#include <abstractions/secp256k1.hpp>

namespace abstractions
{

    bool valid(const secp256k1::pubkey& pk) {
        if (!(pk[0] == secp256k1::point_sign_even || pk[0] == secp256k1::point_sign_odd)) return false;
                
        for (int i = 1; i < secp256k1::secret_size; i++) {
            if (pk[i] < secp256k1::max_public_key[i - 1]) break;
            if (pk[i] > secp256k1::max_public_key[i - 1]) return false;
        }
                
        for (int i = 1; i < secp256k1::pubkey_size; i++) {
            if (pk[i] != 0) return true;
        }
                
        return false;
    }

    inline bool valid(const secp256k1::secret& pk) {
        return pk != secp256k1::secret{};
    }
    
}
