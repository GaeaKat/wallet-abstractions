#ifndef ABSTRACTIONS_INVALID_HPP
#define ABSTRACTIONS_INVALID_HPP

#include "fundamental.hpp"
#include "optional.hpp"

namespace abstractions 
{
    
    template <typename X>
    const X* invalid<X*> = nullptr;

    template <typename X>
    const pointer<X> invalid<pointer<X>> = nullptr;
    
    template <typename X>
    const optional<X> invalid<optional<X>>{};

}

#endif
