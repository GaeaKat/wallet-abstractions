#include <hd.hpp>
#include <bip32.hpp>
#include <trezor/bip32.hpp>

extern "C" {
#include <trezor-crypto/bip32.h>
}

namespace hd
{

namespace bip32
{

// implementations of algebra and to_public using the trezor-crypto library. 
namespace trezor
{

node::node(HDNode n):trezor_error(0),trezor_node(n) {} 

node zero(0, 0, bip32::zero_chain_code, bip32::zero_private_key, bip32::zero_public_key, nullptr);
    
node::node():trezor_error(1) {
    trezor_node = zero.trezor_node;
}

node::node(
    uint32_t depth,
    uint32_t child_num,
    bip32::chain_code chain_code,
    bip32::private_key private_key,
    bip32::public_key public_key,
    const curve_info* curve) : trezor_error(0) {
    trezor_node.depth = depth;
    trezor_node.child_num = child_num;
    trezor_node.curve = curve;
    copy(chain_code.begin(), chain_code.end(), trezor_node.chain_code);
    copy(public_key.begin(), public_key.end(), public_key.chain_code);
    copy(private_key.begin(), private_key.end(), private_key.chain_code);
}

const node public_derive(const node n, const uint32_t i) const {
    node derived = n;
        
    derived.trezor_error = hdnode_public_ckd(&derived.trezor_node, i);
        
    return derived;
}

const node private_derive(const node n, const uint32_t i) const {
    node derived = n;
        
    derived.trezor_error = hdnode_private_ckd(&derived.trezor_node, i);
        
    return derived;
}

}
    
}
    
}
