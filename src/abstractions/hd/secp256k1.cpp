#include <abstractions/hd/secp256k1.hpp>

namespace abstractions
{
    template<> hd::secp256k1::chain_code zero<hd::secp256k1::chain_code> = hd::secp256k1::zero_chain_code;
}

