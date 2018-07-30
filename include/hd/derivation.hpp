#ifndef HD_DERIVATION_HPP
#define HD_DERIVATION_HPP

#include "algebra.hpp"

namespace abstractions
{

namespace hd
{
 
template<typename M>
struct node {
    M First;
    const node* const Rest;
    
    node(M m, const node* const r) : First(m), Rest(r) {}
    virtual ~node() {
        delete Rest;
    }
};

template<typename M>
using list = const node<M>* const;

// A representation of a chain of operations which create a
// particular key. 
template<typename M>
using derivation = list<M>;

// We have to use recursion because we don't know if we can
// create an object of type K. 
template<typename K, typename M>
K derive(algebra<K, M> a, K k, derivation<M> d) {
    if (d == nullptr) {
        return k;
    }
    
    return derive_from_path(a, a(k, d.First), d.Rest);
}

template<typename K, typename R>
R reduce(R zero, R (*const value)(K), R (*const plus)(K, R), list<K> z) {
    if (z == nullptr) {
        return zero;
    }
    
    return plus(value(z->First), reduce(zero, value, plus, z->Rest));
}

}

}

#endif

