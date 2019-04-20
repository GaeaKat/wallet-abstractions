#ifndef ABSTRACTIONS_WALLET_SPENDABLE
#define ABSTRACTIONS_WALLET_SPENDABLE

#include <abstractions/wallet/keys.hpp>
#include <abstractions/wallet/address.hpp>
#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace wallet {
        
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
