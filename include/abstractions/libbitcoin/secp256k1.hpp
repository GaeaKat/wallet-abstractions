#ifndef ABSTRACTIONS_LIBBITCOIN_KEY_HPP
#define ABSTRACTIONS_LIBBITCOIN_KEY_HPP

#include <abstractions/secp256k1.hpp>

#include <bitcoin/bitcoin/math/elliptic_curve.hpp>

namespace abstractions
{
        
    typedef libbitcoin::ec_compressed ec_compressed;
    typedef libbitcoin::ec_secret ec_secret;
    
    inline ec_compressed libbitcoin_to_public(ec_secret s) {
        libbitcoin::ec_compressed e;
        if (!libbitcoin::secret_to_public(e, s)) return zero<ec_compressed>;
        return e;
    }
    
    inline const secp256k1::pubkey secp256k1::to_public(const secret& s) {
        return libbitcoin_to_public(static_cast<std::array<uint8_t, secp256k1::secret_size>>(s));
    };

}

#endif
