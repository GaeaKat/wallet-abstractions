#ifndef ABSTRACTIONS_MATH_ASSOCIATIVITY_HPP
#define ABSTRACTIONS_MATH_ASSOCIATIVITY_HPP

#include <abstractions/logic/contradiction.hpp>

namespace abstractions {
    
    namespace math {
        
        namespace associative {
    
            template <typename X>
            struct times {
                void associativity(X a, X b, X c) const {
                    if (a * b * c != a * (b * c)) contradiction();
                }
            };
    
            template <typename X>
            struct plus {
                void associativity(X a, X b, X c) const {
                    if (a + b + c != a + (b + c)) contradiction();
                }
            };
            
        }
    
    }
    
}

#endif
