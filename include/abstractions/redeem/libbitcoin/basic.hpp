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
        typedef const libbitcoin::chain::script script;
        
        typedef const libbitcoin::chain::output_point outpoint;
        typedef const libbitcoin::chain::transaction transaction;
        typedef const libbitcoin::chain::transaction transaction;
        
        typedef const libbitcoin::ec_compressed ec_compressed;
        typedef const libbitcoin::ec_secret ec_secret;
        
        // We use the short hash as the address instead of a normal bitcoin payment
        // address because 
        typedef const libbitcoin::short_hash address;
        typedef const libbitcoin::machine::operation operation;
        
        const uint32_t script_version = 1;
        const uint8_t sighash = libbitcoin::machine::sighash_algorithm::all;
        
        inline bool match_p2pksh(script s) {
            return libbitcoin::chain::script::is_pay_key_hash_pattern(s.operations());
        } 
        
        vector<address> get_address_from_p2pksh(script s) {
            operation addr = s.operations()[3];
            if (addr == libbitcoin::machine::operation()) return {};
            return {libbitcoin::bitcoin_short_hash(addr.data())};
        }
        
        struct incomplete_tx : vertex<outpoint> {
            N Value() const final override {
                
            };
            
            bytestring serialize() const final override {
                
            };
        };
        
        struct p2pksh : word<script, outpoint> {
            ec_secret secret;
            ec_compressed pubkey;
            
            script speak(output<script> prev, vertex<outpoint>, uint32_t input_index) const final override {
                // construct a libbitcoin transaction from the vertex. 
                
                // sign
                libbitcoin::endorsement out;
                script::create_endorsement(out, secret, prev.Pubkey, tx, input_index, all, script_version, prev.Value);
                
                return script({out, pubkey});
            };
            
            p2pksh(ec_secret secret, ec_compressed pubkey) : {}
        };
        
        struct p2pksh : association<script, outpoint, address, accomplishment> {            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint> imagine(vector<address>, accomplishment) const {
                
            };
            
            p2pksh() : association<script, outpoint, address, accomplishment>(match_p2pksh, get_address_from_p2pksh) {}
        };
    }
}

#endif
