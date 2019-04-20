#ifndef ABSTRACTIONS_ADDRESS
#define ABSTRACTIONS_ADDRESS

#include <abstractions/pattern.hpp>

namespace abstractions {

    template <
        typename addr,       // the type of the Bitcoin address.
        typename hash,       // a hash function. 
        typename pk,         // a public key. 
        typename sk,         // a secret key.
        typename script,     // scripting language. 
        typename pay_to,      
        typename redeem,     
        typename tx,         // a transaction
        typename interpreter // an iterpreter.
    > struct address :
        public data::crypto::one_way<hash, pk, addr>, 
        public data::function::definition<pay_to, addr, script>, 
        public pattern<pk, sk, script, data::function::composition<pk, script, pay_to, hash>, redeem, tx, interpreter>{};

    }
    
} 

#endif
