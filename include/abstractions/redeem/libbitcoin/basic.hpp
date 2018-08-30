#ifndef ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP
#define ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP

#include <bitcoin/bitcoin/chain/transaction.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include <abstractions/redeem/mind.hpp>
#include <abstractions/redeem/could.hpp>
#include <bitcoin/bitcoin/machine/sighash_algorithm.hpp>

namespace abstractions 
{
    namespace redeem
    {
        typedef const libbitcoin::machine::operation::list script;
        
        typedef const libbitcoin::chain::output_point outpoint;
        typedef const libbitcoin::chain::output output;
        typedef const libbitcoin::chain::transaction tx;
        
        typedef const libbitcoin::ec_compressed ec_compressed;
        typedef const libbitcoin::ec_secret ec_secret;
        
        // We use the short hash as the address instead of a normal bitcoin payment
        // address because 
        typedef const libbitcoin::short_hash address;
        typedef const libbitcoin::machine::operation operation;
        
        const libbitcoin::machine::script_version script_version = libbitcoin::machine::script_version::zero;
        const uint8_t sighash = libbitcoin::machine::sighash_algorithm::all;
        
        vector<address> get_address_from_p2pksh(script s) {
            operation addr = s[3];
            if (addr == libbitcoin::machine::operation()) return {};
            return {libbitcoin::bitcoin_short_hash(addr.data())};
        }
        
        tx tx_from_vertex(vertex<outpoint, output>);
        
        struct word_pay_to_public_key_hash : word<script, outpoint, output> {
            ec_secret secret;
            ec_compressed pubkey;
            
            script speak(N value, script prevout, vertex<outpoint, output> x, uint32_t input_index) const final override {
                libbitcoin::endorsement out;
                libbitcoin::chain::script::create_endorsement(out, secret, prevout, tx_from_vertex(x), input_index, all, script_version, value);
                
                return {out, libbitcoin::to_chunk(pubkey)};
            };
            
            word_pay_to_public_key_hash(ec_secret secret, ec_compressed pubkey) : {}
        };
        
        struct pay_to_public_key_hash : association<script, outpoint, output, address, accomplishment> {            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint, output> imagine(vector<address>, accomplishment) const {
                
            };
            
            pay_to_public_key_hash() : association<script, outpoint, output, address, accomplishment>(libbitcoin::chain::script::is_pay_key_hash_pattern, get_address_from_p2pksh) {}
        };
    }
}

#endif
