// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_TRANSACTION
#define SATOSHI_SV_TRANSACTION

#include <abstractions/crypto/hash/sha256.hpp>
#include <data/crypto/secp256k1.hpp>

#include <abstractions/abstractions.hpp>

#include <satoshi_sv/src/primitives/transaction.h>

#include <satoshi_sv/sv.hpp>

namespace abstractions::sv {
        
    class transaction : private CTransaction {
        using input = CTxIn;
        using output = CTxOut;
        using tx = CTransaction;
        
    public: 
            
        transaction() : CTransaction{} {}
        transaction(tx& t) : CTransaction{t} {}
            
        const slice<output> outputs() {
            return slice<output>::make(CTransaction::vout);
        }
            
        const slice<input> inputs() {
            return slice<input>::make(CTransaction::vin);
        }
            
        sha256::digest hash() {
            return convert(CTransaction::GetHash());
        }
    };
    
} 

#endif
