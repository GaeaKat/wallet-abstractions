#ifndef LIBBITCOIN_SECP256K1_HPP
#define LIBBITCOIN_SECP256K1_HPP

#include <abstractions/data.hpp>
#include <abstractions/sha256.hpp>
#include <abstractions/machine.hpp>
#include <abstractions/key.hpp>
#include <abstractions/secp256k1.hpp>
#include <abstractions/sha256.hpp>
#include <abstractions/bitcoin/script.hpp>

#include <bitcoin/bitcoin/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/chain/transaction.hpp>
#include <bitcoin/bitcoin/machine/interpreter.hpp>

namespace abstractions 
{
    
    namespace secp256k1 {
    
        inline const pubkey to_public(const secret& s) {
            libbitcoin::ec_compressed x;
            libbitcoin::secret_to_public(x, s);
            return x;
        }
        
        inline pubkey pubkey::operator+(const pubkey p) const {
            libbitcoin::ec_compressed x = *this;
            if (!libbitcoin::ec_sum(x, {p})) return pubkey{};
            return x;
        }
        
        inline pubkey pubkey::operator*(const secret s) const {
            libbitcoin::ec_compressed x = *this;
            if (!libbitcoin::ec_multiply(x, s)) return pubkey{};
            return x;
        }
    
    }

    namespace libbitcoin
    {
    
        namespace ec
        {
        
            struct to_public {
                secp256k1::pubkey operator()(const secp256k1::secret& s) const {
                    return secp256k1::to_public(s);
                }
            };
            
            using pubkey = key::pubkey<to_public, secp256k1::pubkey, secp256k1::secret>;
            using pair = key::pair<to_public, secp256k1::pubkey, secp256k1::secret>;
        
        }

    }
    
} 

#endif

