#ifndef ABSTRACTIONS_ABSTRACTIONS
#define ABSTRACTIONS_ABSTRACTIONS

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
    
    using index = uint32_t;

}

#endif
