#ifndef ABSTRACTIONS_HD_BIP32_HPP
#define ABSTRACTIONS_HD_BIP32_HPP

#include <array>

namespace abstractions
{

// A function which transforms objects of type K to type P
// representing a public-key schema. I haven't really needed
// this one for anything yet. 
template<typename K, typename P>
using to_public = P (*)(K);

namespace hd
{

namespace bip32
{

typedef const uint32_t child_index;
typedef uint8_t byte;

// possible types that could be used with an implementation of bip32.
const uint public_key_size = 33;
const uint private_key_size = 32;
const uint chain_code_size = 32;

const byte point_sign_even = 0x02;
const byte point_sign_odd = 0x03;

using public_key = std::array<byte, public_key_size>;
using private_key = std::array<byte, private_key_size>;
using chain_code = std::array<byte, chain_code_size>;

bool valid_public_key(const public_key&);

bool valid_private_key(const private_key&);

bool valid_chain_code(const chain_code&);

const public_key zero_public_key({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
const private_key zero_private_key({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
const chain_code zero_chain_code(zero_private_key);

struct public_node {
    public_key Point;
    chain_code ChainCode;
    
    bool valid() const {
        return valid_public_key(Point) && valid_chain_code(ChainCode);
    }
    
    bool operator==(const public_node& n) const {
        return Point == n.Point && ChainCode == n.ChainCode;
    }
    
    bool operator!=(const public_node& n) const {
        return Point != n.Point || ChainCode != n.ChainCode;
    }
    
    public_node() : Point(zero_public_key), ChainCode(zero_chain_code) {}
    public_node(
        const public_key p,
        const chain_code c) : Point(p), ChainCode(c) {}
};

struct private_node {
    public_node Pubkey;
    private_key Secret;
    
    bool valid() const {
        return valid_private_key(Secret) && Pubkey.valid();
    }
    
    bool operator==(const private_node& n) const {
        return Pubkey == n.Pubkey && Secret == n.Secret;
    }
    
    bool operator!=(const private_node& n) const {
        return Pubkey != n.Pubkey || Secret != n.Secret;
    }
    
    private_node() : Secret(zero_private_key), Pubkey() {}
    private_node(
        const private_key s,
        const public_key p,
        const chain_code c) : Pubkey(p, c), Secret(s) {}
        
    private_node(
        to_public<private_key, public_key> tp,
        const private_key s,
        const chain_code c) : private_node(s, tp(s), c) {}
};

const std::array<byte, public_key_size - 1> max_public_key({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F});

// in bip32, there are two kinds of derivations. Hardened and unhardened.
// A transformation which is hardened is denoted by having the hardened_flag
// set. In otherwords if it is larger than 2^31. 
const child_index hardened_flag = 0x80000000;

}

}

}

#endif

