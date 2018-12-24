#ifndef ABSTRACTIONS_ABSTRACTIONS_HPP
#define ABSTRACTIONS_ABSTRACTIONS_HPP

#include "invalid.hpp"

namespace abstractions 
{

    using N = unsigned long long int;

    const N all = N(0 - 1);

    const N aleph_0 = all / 2 + 1;

    template<> N invalid<N> = aleph_0;
    
    inline const N plus(const N n, const N m) {
        return n + m;
    }

    using Z = const long long int;

    template<> Z invalid<Z> = aleph_0;

}

#endif
