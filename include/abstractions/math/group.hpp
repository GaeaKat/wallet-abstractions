#ifndef ABSTRACTIONS_MATH_GROUP_HPP
#define ABSTRACTIONS_MATH_GROUP_HPP

#include <abstractions/math/associativity.hpp>
#include <abstractions/logic/contradiction.hpp>

namespace abstractions {
    
    namespace math {
    
        template <typename X>
        struct group : public associative::times<X> {
            virtual X identity() const = 0;
            
            void identity_definition(X x) const {
                 if (identity() * x != x) contradiction();
            }
            
            virtual X inverse(X) const = 0;
            
            void inverse_definition(X x) const {
                 if (identity() != inverse(x) * x) contradiction();
            };
            
        };
    
    }
    
}

#endif

