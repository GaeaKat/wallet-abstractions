#ifndef ABSTRACTIONS_ABSTRACTIONS_HPP
#define ABSTRACTIONS_ABSTRACTIONS_HPP

#include "invalid.hpp"

namespace abstractions 
{

    template <typename X>
    extern const X zero;

    template <typename X>
    const X zero = X(0);

    // the identity function is always possible. 
    template <typename anything>
    anything identity (anything a) {
        return a;
    }

    using N = const unsigned long long int;

    N all = N(zero<N> - 1);

    N aleph_0 = all / 2 + 1;

    template<> N invalid<N> = aleph_0;
    
    inline const N plus(const N n, const N m) {
        return n + m;
    }

    using Z = const long long int;

    template<> Z invalid<Z> = aleph_0;

}

#endif
