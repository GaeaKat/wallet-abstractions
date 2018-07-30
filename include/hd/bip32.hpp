#ifndef HD_BIP32_HPP
#define HD_BIP32_HPP

#include <array>

namespace abstractions
{

namespace hd
{

// namespace bip32 contains material directly related to bip32. 
namespace bip32
{

typedef const uint32_t child_index;
typedef const uint8_t byte;

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

struct public_key : std::array<byte, public_key_size> {
    public_key();
    public_key(public_key const &p) : std::array<byte, public_key_size>(p) {}
    public_key(std::array<byte, public_key_size> p) : std::array<byte, public_key_size>(p) {}
};

struct private_key: std::array<byte, private_key_size> {
    private_key();
    private_key(private_key const &p) : std::array<byte, private_key_size>(p) {}
    private_key(std::array<byte, private_key_size> p) : std::array<byte, private_key_size>(p) {}
};

struct chain_code : std::array<byte, chain_code_size> {
    chain_code();
    chain_code(chain_code const &p) : std::array<byte, chain_code_size>(p) {}
    chain_code(std::array<byte, chain_code_size> p) : std::array<byte, chain_code_size>(p) {}
};

const public_key zero_public_key({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
const private_key zero_private_key({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
const chain_code zero_chain_code(zero_private_key);

public_key::public_key() : std::array<byte, public_key_size>(zero_public_key) {}
private_key::private_key() : std::array<byte, private_key_size>(zero_private_key) {}
chain_code::chain_code() : std::array<byte, chain_code_size>(zero_chain_code) {}

const public_key max({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F});

struct public_node {
    const public_key Pubkey;
    const chain_code ChainCode;
    
    public_node() : Pubkey(), ChainCode() {}
    public_node(public_key p, chain_code c) : Pubkey(p), ChainCode(c) {}
};

struct private_node : public_node {
    const private_key Secret;
    
    private_node() : public_node(), Secret() {}
    private_node(private_key s, public_key p, chain_code c) : public_node(p, c), Secret(s) {}
};

}

}

}

#endif

