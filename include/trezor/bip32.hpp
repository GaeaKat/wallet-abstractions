#ifndef HD_TREZOR_BIP32_HPP
#define HD_TREZOR_BIP32_HPP

#include <hd.hpp>
#include <bip32.hpp>

extern "C" {
#include <trezor-crypto/bip32.h>
}

namespace hd
{
    
namespace bip32
{

namespace trezor
{

struct node {
    HDNode trezor_node;
    
    // trezor-crypto indicates an error by returning 1 for error and 0 for success.
    int trezor_error; 
    
    node();
    node(HDNode n);
    node(uint32_t depth, uint32_t child_num, bip32::chain_code, bip32::private_key, bip32::public_key, const curve_info* curve);
};

const node public_derive(const node, uint32_t);

const node private_derive(const node, uint32_t);

// should be able to generate theories very easily out of these. 

}

}

}

#endif
