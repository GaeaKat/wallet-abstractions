// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_ABSTRACTIONS
#define ABSTRACTIONS_ABSTRACTIONS

#include <cstdint>

namespace abstractions 
{

    using N = unsigned long long int;

    const N all = N(0 - 1);

    const N aleph_0 = all / 2 + 1;
    
    inline const N plus(const N n, const N m) {
        return n + m;
    }

    using Z = const long long int;
    
    using satoshi = N;
    
    const satoshi empty = 0;
    
    using index = uint32_t;

}

#endif
