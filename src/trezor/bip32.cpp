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
    index child_num,
    bip32::chain_code chain_code,
    bip32::private_key private_key,
    bip32::public_key public_key,
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
    for (int i = 0; i < chain_code_size; i++) {
        if (trezor_node.chain_code[i] != n.trezor_node.chain_code[i]) return false;
    }
    
    for (int i = 0; i < public_key_size; i++) {
        if (trezor_node.public_key[i] != n.trezor_node.public_key[i]) return false;
    }
    
    for (int i = 0; i < private_key_size; i++) {
        if (trezor_node.private_key[i] != n.trezor_node.private_key[i]) return false;
    }
    
    return true;
}

const node public_derive(const node n, index i) {
    node derived = n;
        
    derived.trezor_error = hdnode_public_ckd(&derived.trezor_node, i);
        
    return derived;
}

const node private_derive(const node n, index i) {
    node derived = n;
        
    derived.trezor_error = hdnode_private_ckd(&derived.trezor_node, i);
        
    return derived;
}

}
    
}
    
}
