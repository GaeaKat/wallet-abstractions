#ifndef HD_BIP32_HPP
#define HD_BIP32_HPP

#include "hd.hpp"

#include <array>

namespace hd
{

// namespace bip32 contains material directly related to bip32. 
namespace bip32
{

typedef uint32_t child_index;

// in bip32, there are two kinds of derivations. Hardened and unhardened.
// A transformation which is hardened is denoted by having the hardened_flag
// set. In otherwords if it is larger than 2^31. 
const child_index hardened_flag = 0x80000000;

inline bool hardened(child_index x) {
    return (x & hardened_flag) == hardened_flag;
}

// possible types that could be used with an implementation of bip32.
const uint public_key_size = 33;
const uint private_key_size = 32;
const uint chain_code_size = 32;

typedef std::array<uint8_t, public_key_size> public_key;
typedef std::array<uint8_t, private_key_size> private_key;
typedef std::array<uint8_t, chain_code_size> chain_code;

const public_key zero_public_key = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const private_key zero_private_key = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const chain_code zero_chain_code = zero_private_key;

struct public_node {
    public_key Pubkey;
    chain_code ChainCode;
    
    public_node() : Pubkey(), ChainCode() {}
    public_node(public_key p, chain_code c) : Pubkey(p), ChainCode(c) {}
};

struct private_node : public_node {
    private_key Secret;
    
    private_node() : public_node(), Secret() {}
    private_node(private_key s, public_key p, chain_code c) : public_node(p, c), Secret(s) {}
};

}

}

#endif

