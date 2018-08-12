#ifndef ABSTRACTIONS_REDEEM_MEMORY_HPP
#define ABSTRACTIONS_REDEEM_MEMORY_HPP

#include<abstractions.hpp>

namespace abstractions 
{
    // redeem contains a high-level way of redeeming bitcoin txs.
    namespace redeem
    {
        template<
            typename function,       // something that we must invert in order to redeem later. 
            typename knowledge,      // information about how to invert this function. 
            typename will>           // a desired outcome one might have concerning these functions. 
        struct memory {
            // my_output represents an output that we own and information
            // about how we own it. In other words, stuff like do we
            // have all necessary keys? Do we have some keys but not all?
            struct posession {
                function Output;
                
                // truth claims concerning this output. 
                // (such as what information we have about it.) 
                // Also may contain an index as to how tho find that 
                // information. The sky's the limit. 
                knowledge Claim; 
                
                posession(function o, knowledge c) : Output(o), Claim(c) {}
            };
            
            // should we remember this observation given this known information about it for the given purpose?
            virtual bool remember(posession identification, will purpose) const = 0;
        };
    }
}

#endif
