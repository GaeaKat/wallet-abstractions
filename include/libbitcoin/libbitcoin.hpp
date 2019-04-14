#ifndef LIBBITCOIN_LIBBITCOIN
#define LIBBITCOIN_LIBBITCOIN

#include <data/crypto/sha256.hpp>
#include <abstractions/crypto/secp256k1.hpp>

#include <abstractions/data.hpp>
#include <abstractions/machine.hpp>
#include <abstractions/key.hpp>
#include <abstractions/bitcoin/script.hpp>

#include <bitcoin/system/chain/header.hpp>
#include <bitcoin/system/chain/output.hpp>
#include <bitcoin/system/chain/transaction.hpp>
#include <bitcoin/system/machine/interpreter.hpp>

namespace abstractions {

    namespace libbitcoin {
        
        using digest = ::libbitcoin::system::hash_digest;
        
        struct header {
            ::libbitcoin::system::chain::header Header;
            
            header() : Header{} {}
            header(::libbitcoin::system::chain::header h) : Header{h} {}
            
            bool valid() const {
                return Header.is_valid();
            }
            
            ::libbitcoin::system::uint256_t pow() const {
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
            using tx = ::libbitcoin::system::chain::transaction;
            using output = ::libbitcoin::system::chain::output;
            using input = ::libbitcoin::system::chain::input;
        
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
            using script = ::libbitcoin::system::machine::operation::list;
            using program = ::libbitcoin::system::machine::program;
            
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
                return ::libbitcoin::system::machine::interpreter::run(p);
            }
            
            static std::error_code run(bitcoin::script::input_index<transaction> i, script& input, script& output) {
                script s = concatinate(input, output);
                program p{s, i.Transaction.Transaction, static_cast<uint32_t>(i.Index), 0};
                return ::libbitcoin::system::machine::interpreter::run(p);
            }
            
            machine(script input, script output)
                : ErrorCode{run(input, output)} {}
                
            machine(bitcoin::script::input_index<transaction> i, script& input, script& output)
                : ErrorCode{run(i, input, output)} {}
        };
            
    }
    
} 

#endif
