#ifndef ABSTRACTIONS_MATH_ASSOCIATIVITY_HPP
#define ABSTRACTIONS_MATH_ASSOCIATIVITY_HPP

#include <abstractions/math/contradiction.hpp>

namespace abstractions {
    
    namespace math {
        
        namespace associative {
    
            template <typename X>
            struct times {
                void associativity(X a, X b, X c) {
                    equal<X>{a * b * c, a * (b * c)};
                };
            };
    
            template <typename X>
            struct plus {
                void associativity(X a, X b, X c) {
                    equal<X>{a + b + c, a + (b + c)};
                };
            };
            
        }
    
    }
    
}

#endif
