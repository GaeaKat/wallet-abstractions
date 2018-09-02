#include <abstractions/set.hpp>

namespace abstractions
{
    template <typename X>
    set<X> set<X>::operator+(X x) const {
        throw 0;
    }
    
    template <typename X>
    set<X> set<X>::operator-(X x) const {
        throw 0;
    }
    
    template <typename X>
    set<X> set<X>::operator&(set<X> s) const {
        throw 0;
    }
    
    template <typename X>
    set<X> set<X>::operator|(set<X> s) const {
        throw 0;
    }
    
    template <typename X>
    set<X> set<X>::operator/(set<X> s) const {
        throw 0;
    }
    
}
