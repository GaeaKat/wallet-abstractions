#ifndef ABSTRACTIONS_PATTERN
#define ABSTRACTIONS_PATTERN

#include <data/crypto/keypair.hpp>
#include <abstractions/machine.hpp>

namespace abstractions {
        
    template <
        typename pk,
        typename sk,
        typename script, 
        typename pay,
        typename redeem, 
        typename tx, 
        typename interpreter
    > struct pattern : 
        public data::crypto::keypair<pk, sk>, 
        public data::function::definition<pay, pk, script>, 
        public machine::definition<interpreter, script, tx> {
        
        static void required(pk pubkey, sk secret, pay p, redeem r, tx t, interpreter i) {
            assert(i.run(p(pubkey), r(secret, t), t));
        }
    };
    
} 

#endif
