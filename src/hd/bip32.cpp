#include<abstractions/hd/bip32.hpp>

namespace abstractions
{

    namespace hd
    {

        namespace bip32
        {
            bool valid_public_key(const public_key& pk) {
                if (!(pk[0] == point_sign_even || pk[0] == point_sign_odd)) return false;
                
                for (int i = 1; i < public_key_size; i++) {
                    if (pk[i] < max_public_key[i - 1]) break;
                    if (pk[i] > max_public_key[i - 1]) return false;
                }
                
                for (int i = 1; i < public_key_size; i++) {
                    if (pk[i] != 0) return true;
                }
                
                return false;
            }

            bool valid_private_key(const private_key& pk) {
                return pk != zero_private_key;
            }

            bool valid_chain_code(const chain_code& cc) {
                return cc != zero_chain_code;
            }
            
        }
        
    }
    
}
