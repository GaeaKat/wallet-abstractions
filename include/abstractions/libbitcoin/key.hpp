#ifndef ABSTRACTIONS_LIBBITCOIN_KEY_HPP
#define ABSTRACTIONS_LIBBITCOIN_KEY_HPP

#include <abstractions/key.hpp>

#include <bitcoin/bitcoin/math/elliptic_curve.hpp>

namespace abstractions
{
        
    typedef libbitcoin::ec_compressed ec_compressed;
    typedef libbitcoin::ec_secret ec_secret;
    
    template<> const ec_compressed zero_pubkey<ec_compressed> = ::libbitcoin::null_compressed_point;
    
    template<> const ec_secret zero_secret<ec_secret> = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    
    inline ec_compressed libbitcoin_to_public(ec_secret s) {
        libbitcoin::ec_compressed e;
        if (!libbitcoin::secret_to_public(e, s)) return zero_pubkey<ec_compressed>;
        return e;
    }
    
    inline const key<ec_secret, ec_compressed> libbitcoin_key(ec_secret s, ec_compressed c) {
        return key<ec_secret, ec_compressed>(s, c, libbitcoin_to_public);
    }
    
    inline const key<ec_secret, ec_compressed> libbitcoin_key(ec_secret s) {
        return libbitcoin_key(s, libbitcoin_to_public(s));
    }

}

#endif
