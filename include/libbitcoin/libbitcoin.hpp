#ifndef LIBBITCOIN_LIBBITCOIN_HPP
#define LIBBITCOIN_LIBBITCOIN_HPP

#include <abstractions/data.hpp>
#include <abstractions/sha256.hpp>
#include <abstractions/machine.hpp>
#include <abstractions/key.hpp>
#include <abstractions/secp256k1.hpp>
#include <abstractions/sha256.hpp>
#include <abstractions/bitcoin/script.hpp>

#include <bitcoin/bitcoin/chain/header.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/chain/transaction.hpp>
#include <bitcoin/bitcoin/machine/interpreter.hpp>

namespace abstractions 
{
    
    inline const secp256k1::pubkey to_public(const secp256k1::secret& s) {
        ::libbitcoin::ec_compressed x;
        ::libbitcoin::secret_to_public(x, s);
        return x;
    }

    namespace libbitcoin
    {
    
        namespace ec
        {
        
            struct to_public {
                secp256k1::pubkey operator()(const secp256k1::secret& s) const {
                    return secp256k1::pubkey(this->operator()(static_cast<const std::array<byte, secp256k1::secret_size>&>(s)));
                }
            };
            
            using pubkey = key::pubkey<to_public, secp256k1::pubkey, secp256k1::secret>;
            using pair = key::pair<to_public, secp256k1::pubkey, secp256k1::secret>;
        
        }
        
        namespace btc {
            
            using digest = ::libbitcoin::hash_digest;
            
            struct header {
                ::libbitcoin::chain::header Header;
                
                header() : Header{} {}
                header(::libbitcoin::chain::header h) : Header{h} {}
                
                bool valid() const {
                    return Header.is_valid();
                }
                
                ::libbitcoin::uint256_t pow() const {
                    return Header.proof();
                }
            
                digest hash() const {
                    return Header.hash();
                }
            
                digest root() const {
                    return Header.merkle();
                }
            
                digest parent() const {
                    return Header.previous_block_hash();
                }
                
            };
            
            class transaction {
                using tx = ::libbitcoin::chain::transaction;
                using output = ::libbitcoin::chain::output;
                using input = ::libbitcoin::chain::input;
            
            public: 
                tx Transaction;
                
                transaction() : Transaction{} {}
                transaction(tx t) : Transaction{t} {}
                
                slice<output> outputs() {
                    return slice<output>{Transaction.outputs()};
                }
                
                slice<input> inputs() {
                    return slice<input>{Transaction.inputs()};
                }
                
                digest hash() {
                    return Transaction.hash();
                }
            };
            
            struct machine {
                using script = ::libbitcoin::machine::operation::list;
                using program = ::libbitcoin::machine::program;
                
                std::error_code ErrorCode;
                
                static script concatinate(script& input, script& output) {
                    script n(input.size() + output.size());
                    std::copy(std::begin(input), std::end(input), std::begin(n));
                    std::copy(std::begin(output), std::end(output), std::back_inserter(n));
                    return n;
                }
                
                static std::error_code run(script& input, script& output) {
                    script s = concatinate(input, output);
                    program p{s};
                    return ::libbitcoin::machine::interpreter::run(p);
                }
                
                static std::error_code run(bitcoin::script::input_index<transaction> i, script& input, script& output) {
                    script s = concatinate(input, output);
                    program p{s, i.Transaction.Transaction, static_cast<uint32_t>(i.Index), 0};
                    return ::libbitcoin::machine::interpreter::run(p);
                }
                
                machine(script input, script output)
                    : ErrorCode{run(input, output)} {}
                    
                machine(bitcoin::script::input_index<transaction> i, script& input, script& output)
                    : ErrorCode{run(i, input, output)} {}
            };
            
        }

    }
    
} 

#endif
