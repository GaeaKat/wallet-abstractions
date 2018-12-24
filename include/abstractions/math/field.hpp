#ifndef ABSTRACTIONS_MATH_FIELD_HPP
#define ABSTRACTIONS_MATH_FIELD_HPP

#include <abstractions/math/associativity.hpp>
#include <abstractions/math/commutivity.hpp>
#include <abstractions/math/distributivity.hpp>

namespace abstractions {
    
    namespace math {
    
        template <typename X>
        struct field :
            public associative::plus<X>,
            public commutative::plus<X>,
            public associative::times<X>, public distributive<X> {
            virtual X zero() const = 0;
            
            void zero_definition(X x) const {
                if (x != zero() + x) contradiction();
                if (zero() != zero() * x) contradiction();
            }
            
            virtual X identity() const = 0;
            
            void identity_definition(X x) const {
                if (x != zero()) if (x != identity() * x) contradiction();
            }
            
            virtual X minus(X) const = 0;
            
            void minus_definition(X x) const {
                if(zero() != minus(x) - x) contradiction();
            };
            
            virtual X divide(X) const = 0;
            
            void divide_definition(X x) const {
                if (x != zero()) if (identity() != x * divide(x)) contradiction();
            };

        };

    }

}

#endif
