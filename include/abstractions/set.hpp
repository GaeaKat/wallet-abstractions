#ifndef ABSTRACTIONS_SET_HPP
#define ABSTRACTIONS_SET_HPP

#include "abstractions.hpp"

namespace abstractions
{
    template <typename X> struct node;
    
    template <typename X>
    struct set : public pointer<node<X>> {
        virtual bool contains(X) const;
        bool contains(set<X> s) const;
        
        virtual set<X> operator+(X) const;
        virtual set<X> operator-(X) const;
        virtual set<X> operator&(set<X>) const;
        virtual set<X> operator|(set<X>) const;
        virtual set<X> operator/(set<X>) const;
        
        set(pointer<node<X>> p) : pointer<node<X>>(p) {}
        set() : pointer<node<X>>(nullptr) {}
    };
    
    template <typename X>
    struct node {
        virtual X first() const = 0;
        virtual const set<X>& rest() const = 0;
    };
    
    template <typename X>
    struct list_node : public node<X> {
        X First;
        const set<X> Rest;
        
        X first() const final override {
            return First;
        };
        
        const set<X>& rest() const final override {
            return Rest;
        };
        
        list_node(X x, set<X> r) : First(x), Rest(r) {}
        list_node(X x) : First(x), Rest(nullptr) {}
    };
    
    template <typename X>
    bool set<X>::contains(X x) const {
        if (this == nullptr) return false;
        
        if (this->first() == x) return true;
        
        return this->rest().contains(x);
    }
    
    template <typename X>
    bool set<X>::contains(set<X> s) const {
        if (s == nullptr) return true;
            
        if (!contains(s->first())) return false;
            
        return contains(s->rest());
    }

    template<typename K, typename R>
    R reduce(R zero, R (*const value)(K), R (*const plus)(K, R), set<K> z) {
        if (z == nullptr) {
            return zero;
        }
        
        return plus(value(z->first()), reduce(zero, value, plus, z->rest()));
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
            
            return chain(Next, Last + Next(Last->First));
        }
        
        chain(next<X> n, set<X> s) : Next(n), Last(s) {}
        chain() : Last(), Next(nullptr) {}
    };
}

#endif
