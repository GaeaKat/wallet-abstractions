#ifndef ABSTRACTIONS_REDEEM_MEMORY_HPP
#define ABSTRACTIONS_REDEEM_MEMORY_HPP

#include<abstractions/abstractions.hpp>

namespace abstractions 
{
    namespace redeem
    {
        template<typename function, typename will>
        struct memory {
            bool remember(function, will) const = 0;
        };
    }
}

#endif
