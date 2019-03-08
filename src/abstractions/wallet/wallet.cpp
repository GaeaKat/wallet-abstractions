#include <abstractions/wallet/proto.hpp>

namespace abstractions {
    
    namespace wallet {
        // Some functions that need to be implemented!
        
        address::address(data::secp256k1::pubkey) {
            throw 0;
        }
        
        address::address(data::secp256k1::secret) {
            throw 0;
        }
        
        input redeem(spendable) {
            throw 0; 
        }
        
        script pay_to_address(const address) {
            throw 0;
        }
        
        transaction make_transaction(queue<input>, queue<output>) {
            throw 0;
        }
        
        proto::spent proto::spend(const proto p, satoshi amount, satoshi fee, address to, secret mine) const {
            if (amount + fee > p.Balance) return {};
            
            queue<input> redeemed = data::for_each(redeem, p.Outputs);
            
            output sent{amount, pay_to_address(to)};
            
            satoshi remainder = p.Balance - amount - fee;
            
            address change = address(mine);

            if (remainder <= dust) return spent{make_transaction(redeemed, {sent}), proto{}};
            return spent{make_transaction(redeemed, {{sent, output{remainder, pay_to_address(change)}}}), proto{{spendable{change, remainder, mine}}}};
            
            return {};
        }
        
    }

}
