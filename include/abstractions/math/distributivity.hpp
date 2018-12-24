#ifndef ABSTRACTIONS_MATH_DISTRIBUTIVITY_HPP
#define ABSTRACTIONS_MATH_DISTRIBUTIVITY_HPP

#include <abstractions/math/contradiction.hpp>

namespace abstractions {
    
    namespace math {
        
        template <typename X>
        struct distributive {
            void definition(X a, X x, X y) const {
                equal<X>{a * x + a * y, a * (x + y)};
            }
        };
    
    }
    
}

#endif
