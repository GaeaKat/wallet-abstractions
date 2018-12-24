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
                equal<X>{x, zero() + x};
                equal<X>{zero(), zero() * x};
            }
            
            virtual X identity() const = 0;
            
            void identity_definition(X x) const {
                if (x != zero()) equal<X>{x, identity() * x};
            }
            
            virtual X minus(X) const = 0;
            
            void minus_definition(X x) const {
                equal<X>{zero(), minus(x) - x};
            };
            
            virtual X divide(X) const = 0;
            
            void divide_definition(X x) const {
                if (x != zero()) equal<X>{identity(), divide(x) * x};
            };
            
        };
    
    }
    
}

#endif
