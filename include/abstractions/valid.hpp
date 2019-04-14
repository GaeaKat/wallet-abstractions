#ifndef ABSTRACTIONS_VALID
#define ABSTRACTIONS_VALID

#include "fundamental.hpp"

#include <truth/metaprogramming/which.hpp>

namespace abstractions {
    
    namespace validity {
        
        template <typename X>
        struct has_valid_method {
            bool operator()(const X x) const {
                return x.valid();
            }
        };
        
        template <typename X>
        struct default_valid {
            bool operator()(const X) const {
                return true;
            }
        };
    
        template <typename X>
        struct check {
            bool operator()(X x) const {
                return typename truth::metaprogramming::Which<has_valid_method<X>, default_valid<X>>::Result{}(x);
            }
        };
        
        template <typename X>
        struct check<X*> {
            bool operator()(X x) const {
                return x != nullptr && valid(*x);
            }
        };
        
        template <typename X>
        struct check<pointer<X>> {
            bool operator()(X x) const {
                return x != nullptr && valid(*x);
            }
        };
    
    }

    template <typename X>
    inline bool valid(X x) {      
        return validity::check<X>{}(x);
    }

}

#endif
