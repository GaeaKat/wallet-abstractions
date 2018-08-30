#ifndef ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP
#define ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP

#include <abstractions/libbitcoin/key.hpp>
#include <abstractions/database.hpp>

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
        
        // We use the short hash as the address instead of a normal bitcoin payment
        // address because then we don't have to think about the address type. 
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
            const key<ec_secret, ec_compressed> Key; 
            
            script speak(N value, script prevout, vertex<outpoint, output> x, uint32_t input_index) const final override {
                libbitcoin::endorsement out;
                libbitcoin::chain::script::create_endorsement(out, Key.Secret, prevout, tx_from_vertex(x), input_index, all, script_version, value);
                return {out, libbitcoin::to_chunk(Key.Pubkey)};
            };
            
            word_pay_to_public_key_hash(key<ec_secret, ec_compressed> k) : Key(k) {}
        };
        
        struct pay_to_public_key_hash : association<script, outpoint, output, address, accomplishment> {
            const database<key<ec_secret, ec_compressed>, address>& Database;
            
            // possibly nullptr, as not every mental state is associated with a word. , 
            thought<script, outpoint, output> imagine(vector<address> addrs, accomplishment w) const {
                if (w != redeemed) return nullptr;
                if (addrs.size() != 1) return nullptr;
                
                entry<key<ec_secret, ec_compressed>> e = Database.get(addrs[0]);
                if (!e.Exists) return nullptr;
                
                return std::shared_ptr<word<script, outpoint, output>>(new word_pay_to_public_key_hash(e.Value));
            };
            
            pay_to_public_key_hash(const database<key<ec_secret, ec_compressed>, address>& d)
                : association<script, outpoint, output, address, accomplishment>(
                    libbitcoin::chain::script::is_pay_key_hash_pattern,
                    get_address_from_p2pksh), Database(d) {}
        };
    }
}

#endif
