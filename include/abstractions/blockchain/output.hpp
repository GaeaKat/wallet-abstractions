#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_OUTPUT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    
    namespace bitcoin
    {
    
        namespace output
        {
            
            // How much is stored in a given output?
            template <typename output>
            inline N value(output o) {
                return o.value();
            }
                
            // What is the script defining how this output is redeemed. 
            template <typename output, typename scr>
            inline scr script(output o) {
                return o.script();
            }
        
        }
    
    }
    
} 

#endif
