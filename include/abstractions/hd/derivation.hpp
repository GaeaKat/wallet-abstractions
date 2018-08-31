#ifndef ABSTRACTIONS_HD_DERIVATION_HPP
#define ABSTRACTIONS_HD_DERIVATION_HPP

#include <abstractions/set.hpp>
#include "algebra.hpp"

namespace abstractions
{

namespace hd
{

// A representation of a chain of operations which create a
// particular key. 
template<typename M>
using derivation = set<M>;

// We have to use recursion because we don't know if we can
// create an object of type K. 
template<typename K, typename M>
K derive(algebra<K, M> a, K k, derivation<M> d) {
    if (d == nullptr) {
        return k;
    }
    
    return derive(a, a(k, d->First), d->Rest);
}

}

}

#endif

