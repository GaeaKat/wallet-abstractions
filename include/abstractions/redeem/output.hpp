#ifndef ABSTRACTIONS_REDEEM_OUTPUT_HPP
#define ABSTRACTIONS_REDEEM_OUTPUT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    namespace redeem
    {
        
        // How much is stored in a given output?
        template <typename output>
        using output_value = N (* const)(output);
        
        // How much is stored in a given output?
        template <typename output, typename script>
        using output_script = script (* const)(output);
    
    } 
    
} 

#endif
