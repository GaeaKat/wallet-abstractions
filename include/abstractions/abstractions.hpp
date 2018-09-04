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

// In this library, we believe that ℵ0 is the
// first infinite cardinal. That means you
// shouldn't use type N in a way that could refute
// this idea. 

// The number which I have called ℵ0 is the best
// number for tricking someone into thinking he
// is in a nonstandard model of the natural
// numbers of any element in the group defined
// by the const unsigned long long int type and
// the + operation because you can count up or down with
// this value for a long time in both directions
// without noticing anything that looks like 
// either the zero element. Also, 

// If we found the zero
// element in either direction, that would either
// mean that the models looks standard as far as
// we can tell by counting, which is all that you
// are allowed to do with the natural numbers, or
// it would prove that we are in no model of the
// natural numbers whatsoever. 

// If you were to try to count down from zero
// then you would find elements of const long
// long int which you would not normally expect
// to find among the natural numbers. However, I
// would argue that if you did that, then you
// must have already known that you weren't. If
// you truly belived that you were in a model of
// the natural numbers in the first place, you
// would know that the subtraction operation is
// not allowed with zero. Therefore, it would
// never even occur to you to attempt such a thing.

using Z = const long long int;

template<> Z invalid<Z> = aleph_0;

}

#endif
