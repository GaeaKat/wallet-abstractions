#ifndef LIBBITCOIN_LIBBITCOIN_HPP
#define LIBBITCOIN_LIBBITCOIN_HPP

#include <abstractions/data.hpp>
#include <abstractions/sha256.hpp>
#include <abstractions/machine.hpp>

#include <bitcoin/bitcoin/chain/header.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/chain/transaction.hpp>
#include <bitcoin/bitcoin/machine/interpreter.hpp>

namespace abstractions 
{
    
    namespace libbitcoin_btc {
        
        class header {
            libbitcoin::chain::header Header;
            mutable libbitcoin::hash_digest* Hash;
        
        public:
            header() : Header{}, Hash{nullptr} {}
            header(libbitcoin::chain::header h) : Header{h}, Hash{nullptr} {}
            ~header() {
                delete Hash;
            }
            
            bool valid() const {
                return Header.is_valid();
            }
            
            libbitcoin::uint256_t pow() const {
                return Header.proof();
            }
        
            libbitcoin::hash_digest& hash() const {
                if (Hash == nullptr) Hash = new libbitcoin::hash_digest{Header.hash()};
                return *Hash;
            }
        
            libbitcoin::hash_digest root() const {
                return Header.merkle();
            }
        
            libbitcoin::hash_digest parent() const {
                return Header.previous_block_hash();
            }
            
        };
        
        class transaction {
            libbitcoin::chain::transaction Transaction;
        public:
            transaction() : Transaction{} {}
            transaction(libbitcoin::chain::transaction t) : Transaction{t} {}
            
            slice<libbitcoin::chain::output> outputs() {
                return slice<libbitcoin::chain::output>{Transaction.outputs()};
            }
            
            slice<libbitcoin::chain::input> inputs() {
                return slice<libbitcoin::chain::input>{Transaction.inputs()};
            }
        };
        
        /*class machine {
            constexpr static const abstractions::machine::definition::machine<machine, libbitcoin::chain::script&> require_machine{};
            constexpr static const abstractions::machine::definition::initializeable<machine, abstractions::script::input_index<transaction*>> require_initializable{};
            
            abstractions::script::input_index<transaction*> Index;
        public:
            
            machine() : Index{} {}
            machine(abstractions::script::input_index<transaction*> i) : Index{i} {}
            
            bool run(libbitcoin::chain::script output) {
                if (!Index.valid()) return false;
                libbitcoin::machine::program p{Index.get_input_script<libbitcoin::chain::script>(), , Index.Index, 0};
                return 0 == libbitcoin::machine::interpreter{}.run(p);
            }
        };*/
        
    }
    
} 

#endif
