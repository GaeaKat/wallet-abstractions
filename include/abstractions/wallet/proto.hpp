#ifndef ABSTRACTIONS_WALLET_PROTO
#define ABSTRACTIONS_WALLET_PROTO

#include <abstractions/fundamental.hpp>
#include <abstractions/data.hpp>
#include <abstractions/wallet/address.hpp>
#include <data/crypto/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <data/fold.hpp>
#include <data/for_each.hpp>
#include <data/append.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using satoshi = const uint64_t;
        
        satoshi (*plus)(satoshi, satoshi) = data::plus<satoshi>;
        
        satoshi empty = 0;
        
        using transaction = vector<byte>;
        
        using outpoint = vector<byte>;
        
        using input = vector<byte>;
        
        using secret = const data::secp256k1::secret;
        
        struct spendable final {
            address Address;
            satoshi Amount;
            secret Secret;
        };
        
        input redeem(spendable);
        
        struct proto final {
            satoshi Balance;
            queue<spendable> Outputs;
            
            proto() : Balance{0}, Outputs{} {}
            proto(queue<spendable> l) : Balance{data::fold(plus, empty, l)}, Outputs{} {}
            proto(std::initializer_list<spendable> l) : proto(queue<spendable>{l}) {}
            
            proto fill(const proto p, const spendable s) const;
            
            struct spent;
            
            spent spend(const proto p, satoshi amount, satoshi fee, address to, secret change) const;
            
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
        
        using script = vector<byte>;
        
        struct output {
            satoshi Amount;
            script Script;
        };
        
        transaction make_transaction(queue<input>, queue<output>);
        
        script pay_to_address(const address);
        
        extern const satoshi dust;
        
        proto::spent proto::spend(const proto p, satoshi amount, satoshi fee, address to, secret mine) const {
            if (amount + fee > p.Balance) return {};
            
            queue<input> redeemed = data::for_each(redeem, p.Outputs);
            
            output sent{amount, pay_to_address(to)};
            
            satoshi remainder = p.Balance - amount - fee;
            
            address change = address(mine);

            return remainder <= dust ?
                spent{make_transaction(redeemed, {sent}), proto{}} :
                spent{make_transaction(redeemed, {{sent, output{remainder, pay_to_address(change)}}}), proto{{spendable{change, remainder, mine}}}};
        }

    }

}

#endif

