#include<abstractions/secp256k1.hpp>

namespace abstractions
{

    namespace secp256k1
    {
    
        bool valid(const pubkey& pk) {
            if (!(pk[0] == point_sign_even || pk[0] == point_sign_odd)) return false;
                
            for (int i = 1; i < secret_size; i++) {
                if (pk[i] < max_public_key[i - 1]) break;
                if (pk[i] > max_public_key[i - 1]) return false;
            }
                
            for (int i = 1; i < pubkey_size; i++) {
                if (pk[i] != 0) return true;
            }
                
            return false;
        }

        bool valid(const secret& pk) {
            return pk != zero<secret>;
        }
        
    }
    
}
