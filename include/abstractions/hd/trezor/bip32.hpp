#ifndef ABSTRACTIONS_HD_TREZOR_BIP32_HPP
#define ABSTRACTIONS_HD_TREZOR_BIP32_HPP

#include <abstractions/hd/bip32.hpp>
#include <abstractions/hd/heap.hpp>

extern "C" {
#include <trezor-crypto/bip32.h>
}

namespace abstractions
{

namespace hd
{
    
namespace bip32
{

struct node {
    HDNode trezor_node;
    
    // trezor-crypto indicates an error by returning 1 for error and 0 for success.
    int trezor_error; 
    
    bool operator==(const node& n) const;
    
    node();
    node(HDNode n);
    node(uint32_t depth, child_index child_num, secp256k1::chain_code, secp256k1::private_key, secp256k1::public_key, const curve_info* curve);
};

const node public_derive(const node, uint32_t);

const node private_derive(const node, uint32_t);

algebra<const node, child_index> public_algebra = &public_derive;

algebra<const node, child_index> private_algebra = &private_derive;

// should be able to generate theories very easily out of these. 

// return theories initialized on the heap that the user has to delete
// when he's done with them. 
const error_theory<const node, child_index>* const public_hd_tree(node n) {
    return new heap<const node, child_index>(public_algebra, n);
}

const error_theory<const node, child_index>* const private_hd_tree(node n) {
    return new heap<const node, child_index>(private_algebra, n);
}

// I'm not sure how to make these ones work correctly. 
/*const heap<const node, uint32_t> public_tree_heap(node n) {
    return heap<const node, uint32_t>(public_algebra, n);
}

const heap<const node, uint32_t> private_tree_heap(node n) {
    return heap<const node, uint32_t>(private_algebra, n);
}*/

}

}

}

#endif
