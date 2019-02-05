#ifndef ABSTRACTIONS_WALLET_SPENDABLE_HPP
#define ABSTRACTIONS_WALLET_SPENDABLE_HPP

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using satoshi = const uint64_t;
        
        satoshi empty = 0;
        
        using transaction = vector<byte>;
        
        using outpoint = vector<byte>;
        
        using input = vector<byte>;
        
        struct spendable final {
            address Address;
            satoshi Amount;
            secret Secret;
            
            bool valid() const {
                return Amount != 0;
            }
        };
        
        input redeem(spendable);
        
    }

}

#endif
