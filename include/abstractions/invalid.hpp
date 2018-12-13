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
    
    template <typename X>
    struct check_valid {
        bool operator()(X x) const {
            return x.valid();
        }
    };
    
    template <typename X>
    struct check_valid<X*> {
        bool operator()(X x) const {
            if (x == nullptr) return false;
            return x->valid();
        }
    };
    
    template <typename X>
    struct check_valid<pointer<X>> {
        bool operator()(X x) const {
            return x->valid();
        }
    };

    template <typename X>
    inline bool valid(X x) {        
        return check_valid<X>{}(x);
    }

}

#endif
