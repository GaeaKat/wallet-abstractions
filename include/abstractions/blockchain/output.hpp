#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    
    namespace output
    {
            
        // How much is stored in a given output?
        template <typename output>
        using value = N (* const)(output);
            
        // How much is stored in a given output?
        template <typename output, typename script>
        using script = script (* const)(output);
    
    }
    
} 

#endif
