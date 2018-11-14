#ifndef ABSTRACTIONS_LIST_HPP
#define ABSTRACTIONS_LIST_HPP

#include "abstractions.hpp"

namespace abstractions 
{
    
    template<typename function, typename list, typename value>
    value reduce(function plus, list l, value zero) {
        if (empty(l)) return zero;
        
        return plus(value{first(l)}, reduce(plus, rest(l)));
    }
    
    template<typename list, typename value>
    value reduce(list l, value zero) {
        if (empty(l)) return zero;
        
        return value{first(l)} + reduce(plus, rest(l));
    }
        
    template <typename function, typename from, typename to> 
    to apply(function f, from l) {
        if (empty(l)) return nullptr;
        return apply(f, rest(l)) + f(*first(l));
    }
    
    template <typename function, typename list, typename value>
    value find(function satisfies, list l) {
        if (empty(l)) return value{};
        auto f0 = first(l);
        if (satisfies(f0)) return f0;
        return rest(l);
    }

}

#endif
