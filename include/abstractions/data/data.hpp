#ifndef ABSTRACTIONS_DATA_DATA_HPP
#define ABSTRACTIONS_DATA_DATA_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions
{
    
    namespace data
    {

        template <typename X, typename Y>
        inline bool contains(const X container, const Y elem) {
            return container.contains(elem);
        }
        
    }
    
}

#endif
