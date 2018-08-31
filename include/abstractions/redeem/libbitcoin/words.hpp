#ifndef ABSTRACTIONS_REDEEM_LIBBITCOIN_WORDS_HPP
#define ABSTRACTIONS_REDEEM_LIBBITCOIN_WORDS_HPP

#include <abstractions/redeem/individual.hpp>

#include <abstractions/libbitcoin/secp256k1.hpp>

#include <bitcoin/bitcoin/chain/transaction.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include <bitcoin/bitcoin/machine/sighash_algorithm.hpp>

namespace abstractions 
{
    namespace redeem
    {
        
        typedef const libbitcoin::machine::operation::list script;
        
        typedef const libbitcoin::chain::output_point outpoint;
        typedef const libbitcoin::chain::output output;
        typedef const libbitcoin::chain::transaction tx;
        
        // We use the short hash as the address instead of a normal bitcoin payment
        // address because then we don't have to think about the address type. 
        typedef const libbitcoin::short_hash hash;
        typedef const libbitcoin::machine::operation operation;
        
        const libbitcoin::machine::script_version script_version = libbitcoin::machine::script_version::zero;
        const uint8_t sighash = libbitcoin::machine::sighash_algorithm::all;
        
        vector<hash> get_address_from_p2pksh(script s) {
            operation addr = s[3];
            if (addr == libbitcoin::machine::operation()) return {};
            return {libbitcoin::bitcoin_short_hash(addr.data())};
        }
        
        tx tx_from_vertex(vertex<outpoint, output>);
        
        script libbitcoin_sign_pay_to_public_key_hash(secp256k1::key k, N value, script prevout, vertex<outpoint, output> x, uint32_t input_index) {
            libbitcoin::endorsement out;
            libbitcoin::chain::script::create_endorsement(out, k.Secret, prevout, tx_from_vertex(x), input_index, all, script_version, value);
            return {out, libbitcoin::to_chunk(k.Pubkey)};
        }
        
        inline const individual<secp256k1::key, script, outpoint, output, hash> libbitcoin_pay_to_public_key_hash(
            const database<secp256k1::key, hash>& d
        ) {
            return individual<secp256k1::key, script, outpoint, output, hash>(
                libbitcoin::chain::script::is_pay_key_hash_pattern,
                get_address_from_p2pksh,
                d,
                libbitcoin_sign_pay_to_public_key_hash);
        }
    
    } // redeem
    
} // abstractions

#endif
