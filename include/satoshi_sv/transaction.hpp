#ifndef SATOSHI_SV_TRANSACTION
#define SATOSHI_SV_TRANSACTION

#include <data/crypto/sha256.hpp>
#include <abstractions/crypto/secp256k1.hpp>

#include <abstractions/data.hpp>

#include <primitives/transaction.h>

namespace abstractions {

    namespace satoshi_sv {
        
        using digest = ::uint256;
        
        class transaction : private CTransaction {
            using input = ::CTxIn;
            using output = ::CTxOut;
            using tx = ::CTransaction;
        
        public: 
            
            transaction() : CTransaction{} {}
            transaction(tx& t) : CTransaction{t} {}
            
            const slice<output> outputs() {
                return slice<output>::make(CTransaction::vout);
            }
            
            const slice<input> inputs() {
                return slice<input>::make(CTransaction::vin);
            }
            
            digest hash() {
                return CTransaction::GetHash();
            }
        };
            
    }
    
} 

#endif
