#ifndef HD_TREZOR_BIP32_HPP
#define HD_TREZOR_BIP32_HPP

#include <bip32.hpp>
#include <heap.hpp>

extern "C" {
#include <trezor-crypto/bip32.h>
}

namespace hd
{
    
namespace bip32
{

namespace trezor
{
    
typedef bip32::child_index index;

struct node {
    HDNode trezor_node;
    
    // trezor-crypto indicates an error by returning 1 for error and 0 for success.
    int trezor_error; 
    
    bool operator==(const node& n) const;
    
    node();
    node(HDNode n);
    node(uint32_t depth, index child_num, bip32::chain_code, bip32::private_key, bip32::public_key, const curve_info* curve);
};

const node public_derive(const node, uint32_t);

const node private_derive(const node, uint32_t);

algebra<const node, child_index> public_algebra = &public_derive;

algebra<const node, child_index> private_algebra = &private_derive;

// should be able to generate theories very easily out of these. 

// return theories initialized on the heap that the user has to delete
// when he's done with them. 
const error_theory<const node, index>* const public_hd_tree(node n) {
    return new heap<const node, uint32_t>(public_algebra, n);
}

const error_theory<const node, index>* const private_hd_tree(node n) {
    return new heap<const node, uint32_t>(private_algebra, n);
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
