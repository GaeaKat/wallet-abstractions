#ifndef ABSTRACTIONS_WALLET_SCRIPT
#define ABSTRACTIONS_WALLET_SCRIPT

#include <abstractions/wallet/spendable.hpp>

namespace abstractions {
    
    namespace wallet {
        
        using script = vector<byte>;
        
        namespace hex {
            script read(string& x);
            string write(script& s);
        }

    }

}

#endif

