#ifndef ABSTRACTIONS_SET_HPP
#define ABSTRACTIONS_SET_HPP

#include "abstractions.hpp"

namespace abstractions
{
    template <typename X> struct node;
    
    template <typename X>
    struct set : public pointer<node<X>> {
        virtual bool contains(X) const;
        virtual set<X> operator+(X) const;
        virtual set<X> operator-(X) const;
        virtual set<X> operator&(set<X>) const;
        virtual set<X> operator|(set<X>) const;
        virtual set<X> operator/(set<X>) const;
        
        bool operator==(pointer<node<X>> p) {
            return pointer<node<X>>::operator==(p);
        }
        
        set(pointer<node<X>> p) : pointer<node<X>>(p) {}
        set() : pointer<node<X>>(nullptr) {}
    };
    
    template <typename X>
    struct node {
        X First;
        set<X> Rest;
        
        node(X x, set<X> r) : First(x), Rest(r) {}
        node(X x) : First(x), Rest(nullptr) {}
    };
    
    template <typename X>
    bool set<X>::contains(X x) const {
        if (this == nullptr) return false;
        
        if (this->First == x) return true;
        
        return this->Rest.contains(x);
    }

    template<typename K, typename R>
    R reduce(R zero, R (*const value)(K), R (*const plus)(K, R), set<K> z) {
        if (z == nullptr) {
            return zero;
        }
        
        return plus(value(z->First), reduce(zero, value, plus, z->Rest));
    }
    
    template <typename X>
    using next = X (*const)(X);
    
    template <typename X>
    struct chain {
        next<X> Next;
        set<X> Last;
        
        chain<X> generate_new() const {
            if (Next == nullptr) return nullptr;
            if (Last == nullptr) return nullptr;
            
            return chain(Next, Last+(Next(Last->First)));
        }
        
        chain(next<X> n, set<X> s) : Next(n), Last(s) {}
        chain() : Last(), Next(nullptr) {}
    };
}

#endif
