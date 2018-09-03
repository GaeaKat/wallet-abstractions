#ifndef ABSTRACTIONS_ONE_WAY_HPP
#define ABSTRACTIONS_ONE_WAY_HPP

namespace abstractions
{
    
    template <typename S, typename P>
    using one_way = P (* const)(S);
    
    template<typename S, typename P>
    bool satisfies(one_way<S, P> f, S s, P p) {
        return p == f(s);
    };

}

#endif
