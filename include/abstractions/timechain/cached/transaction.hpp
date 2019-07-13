#ifndef ABSTRACTIONS_BITCOIN_CACHED_TRANSACTION_HPP
#define ABSTRACTIONS_BITCOIN_CACHED_TRANSACTION_HPP

#include <abstractions/bitcoin/transaction.hpp>

namespace abstractions 
{
    
    namespace transaction {
        
        // A header that caches the result of calculating its hash. 
        template <typename tx, typename in, typename out, typename digest>
        struct cached {
            tx Transaction;
            
            slice<out> outputs(tx t) const {
                return outputs(Transaction);
            }
            
            slice<in> inputs(tx t) const {
                return inputs(Transaction);
            }
            
            const digest hash() const {
                if (Digest == digest{}) Digest = hash(Transaction);
                
                return Digest;
            }
            
            cached(tx t) : Transaction{t}, Digest{} {}
            
        private:
            mutable digest Digest;
        };
        
    } 

}

#endif

