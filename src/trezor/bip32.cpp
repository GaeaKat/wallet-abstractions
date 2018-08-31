#include <abstractions/hd/hd.hpp>
#include <abstractions/hd/bip32.hpp>
#include <abstractions/hd/trezor/bip32.hpp>

extern "C" {
#include <trezor-crypto/bip32.h>
}

namespace abstractions
{

    namespace hd
    {

        namespace bip32
        {

            node::node(HDNode n):trezor_error(0),trezor_node(n) {} 

            const node zero_node(0, 0, zero<secp256k1::chain_code>, zero<abstractions::secp256k1::secret>, zero<abstractions::secp256k1::pubkey>, nullptr);
                
            node::node():trezor_error(1) {
                trezor_node = zero_node.trezor_node;
            }

            node::node(
                uint32_t depth,
                child_index child_num,
                secp256k1::chain_code chain_code,
                abstractions::secp256k1::secret private_key,
                abstractions::secp256k1::pubkey public_key,
                const curve_info* curve) : trezor_error(0) {
                trezor_node.depth = depth;
                trezor_node.child_num = child_num;
                trezor_node.curve = curve;
                std::copy(chain_code.begin(), chain_code.end(), trezor_node.chain_code);
                std::copy(public_key.begin(), public_key.end(), trezor_node.public_key);
                std::copy(private_key.begin(), private_key.end(), trezor_node.private_key);
            }
                
            bool node::operator==(const node& n) const {
                bool x = trezor_error == n.trezor_error
                    && trezor_node.depth == n.trezor_node.depth
                    && trezor_node.child_num == n.trezor_node.child_num 
                    && trezor_node.curve == n.trezor_node.curve;
                
                if (!x) return false;
                for (int i = 0; i < secp256k1::chain_code_size; i++) {
                    if (trezor_node.chain_code[i] != n.trezor_node.chain_code[i]) return false;
                }
                
                for (int i = 0; i < abstractions::secp256k1::pubkey_size; i++) {
                    if (trezor_node.public_key[i] != n.trezor_node.public_key[i]) return false;
                }
                
                for (int i = 0; i < abstractions::secp256k1::secret_size; i++) {
                    if (trezor_node.private_key[i] != n.trezor_node.private_key[i]) return false;
                }
                
                return true;
            }

            const node public_derive(const node n, child_index i) {
                node derived = n;
                    
                derived.trezor_error = hdnode_public_ckd(&derived.trezor_node, i);
                    
                return derived;
            }

            const node private_derive(const node n, child_index i) {
                node derived = n;
                    
                derived.trezor_error = hdnode_private_ckd(&derived.trezor_node, i);
                    
                return derived;
            }
            
        }
        
    }

}
