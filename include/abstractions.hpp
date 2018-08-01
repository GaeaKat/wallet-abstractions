#ifndef ABSTRACTIONS_HPP
#define ABSTRACTIONS_HPP

#include<vector>
#include<string>

namespace abstractions 
{

template<typename X> using vector = const std::vector<const X>;

using string = const std::string;

using ℕ = const unsigned long long int;

const ℕ zero = 0;

const ℕ all = ℕ(zero - 1);

const ℕ ℵ0 = all / 2;

}

// The number which I have called ℵ0 is the best
// number for tricking someone into thinking he
// is in a nonstandard model of the natural
// numbers of any element in the group defined
// by the const unsigned long long int type and
// the + operation. 

// Why? because you can count up or down with
// this value for a long time in both directions
// without noticing anything that looks like 
// either the zero element. If we found the zero
// element in either direction, that would either
// mean that the models looks standard as far as
// we can tell by counting, which is all that you
// are allowed to do with the natural numbers, or
// it would prove that we are in no model of the
// natural numbers whatsoever. 

// now if you were to try to count down from zero
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

// Also, the best programmers never need to
// subtract because they know how to program in
// Diophantine equations over the natural numbers. 

// In this library, we believe that ℵ0 is the
// first infinite cardinal. 

#endif
