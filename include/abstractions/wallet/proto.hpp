#ifndef ABSTRACTIONS_WALLET_PROTO
#define ABSTRACTIONS_WALLET_PROTO

#include <abstractions/data.hpp>
#include <abstractions/wallet/output.hpp>
#include <data/crypto/sha256.hpp>
#include <data/fold.hpp>
#include <data/for_each.hpp>
#include <data/append.hpp>

namespace abstractions {
    
    namespace wallet {
        
        inline satoshi add_balance(satoshi total, spendable next){
            return total + next.Amount;
        }
        
        struct proto final {
            satoshi Balance;
            queue<spendable> Outputs;
            
            proto() : Balance{0}, Outputs{} {}
            proto(queue<spendable> l) : Balance{data::fold(add_balance, empty, l)}, Outputs{l} {}
            proto(std::initializer_list<spendable> l) : proto(queue<spendable>{l}) {}
            
            proto fill(const proto p, const spendable s) const;
            
            struct spent;
            
            spent spend(const proto p, satoshi amount, satoshi fee, address to, secret mine) const;
            
        private:
            proto(satoshi b, queue<spendable> o) : Balance{b}, Outputs{o} {}
        };
        
        struct proto::spent {
            transaction Transaction;
            proto Remainder;
                    
            bool valid() const {
                return Transaction.size() > 0;
            }
        };
        
        inline proto proto::fill(const proto p, const spendable s) const {
            return proto{p.Balance + s.Amount, p.Outputs + s};
        }
        
        transaction make_transaction(queue<input>, queue<output>);
        
        script pay_to_address(const address);
        
        extern const satoshi dust;

    }

}

#endif
