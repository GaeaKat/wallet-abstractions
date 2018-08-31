#ifndef ABSTRACTIONS_HD_SECP256K1_HPP
#define ABSTRACTIONS_HD_SECP256K1_HPP

#include <abstractions/secp256k1.hpp>

namespace abstractions
{

    namespace hd
    {

        namespace secp256k1
        {

            const uint chain_code_size = 32;
            
            using public_key = abstractions::secp256k1::pubkey;
            using private_key = abstractions::secp256k1::secret;

            struct chain_code : public std::array<byte, chain_code_size> {
                bool valid() const;
                
                chain_code();
                chain_code(std::array<byte, chain_code_size> a) : std::array<byte, chain_code_size>(a) {}
            };

            bool valid(const chain_code&);
            
            inline bool chain_code::valid() const {
                return secp256k1::valid(*this);
            }

            struct public_node {
                public_key Point;
                chain_code ChainCode;
                
                bool valid() const {
                    return Point.valid() && ChainCode.valid();
                }
                
                bool operator==(const public_node& n) const {
                    return Point == n.Point && ChainCode == n.ChainCode;
                }
                
                bool operator!=(const public_node& n) const {
                    return Point != n.Point || ChainCode != n.ChainCode;
                }
                
                public_node();
                public_node(
                    const public_key p,
                    const chain_code c) : Point(p), ChainCode(c) {}
            };

            struct private_node {
                public_node Pubkey;
                private_key Secret;
                
                bool valid() const {
                    return secp256k1::valid(Secret) && Pubkey.valid();
                }
                
                bool operator==(const private_node& n) const {
                    return Pubkey == n.Pubkey && Secret == n.Secret;
                }
                
                bool operator!=(const private_node& n) const {
                    return Pubkey != n.Pubkey || Secret != n.Secret;
                }
                
                private_node() : Secret(zero<private_key>), Pubkey() {}
                private_node(
                    const private_key s,
                    const public_key p,
                    const chain_code c) : Pubkey(p, c), Secret(s) {}
                    
                private_node(
                    to_public<private_key, public_key> tp,
                    const private_key s,
                    const chain_code c) : private_node(s, tp(s), c) {}
            };
        
        }
    
    }
    
    template<> hd::secp256k1::chain_code zero<hd::secp256k1::chain_code> = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    inline bool hd::secp256k1::valid(const chain_code& cc) {
        return cc != zero<hd::secp256k1::chain_code>;
    }
    
    inline hd::secp256k1::chain_code::chain_code() : std::array<byte, chain_code_size>(zero<hd::secp256k1::chain_code>) {}
    
    inline hd::secp256k1::public_node::public_node() : Point(zero<public_key>), ChainCode(zero<chain_code>) {}

}

#endif
