#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    
    namespace output
    {
        
        // How much is stored in a given output?
        template <typename output>
        N value(output);
            
        // What is the script defining how this output is redeemed. 
        template <typename output, typename scr>
        scr script(output);
    
    }
    
} 

#endif
