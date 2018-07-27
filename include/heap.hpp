#ifndef HD_HEAP_HPP
#define HD_HEAP_HPP

#include "hd.hpp"

namespace hd
{

// Implementation of theory which stores all data
// generated on the heap and releases the memory upon
// distruction of the entire class. should be suitable
// for most purposes, but you could also have a much
// more intelligent implementation that had a database
// and automatic memory management and so on. 
template<typename K, typename M>
class heap : public error_theory<K, M> {    
    typedef typename theory<K, M>::key ideal_key;
    typedef typename theory<K, M>::parent parent;
    
    struct child;
    
    struct key : public ideal_key {
        // mutable because adding childen does not change the key 
        // as it is seen publicly. 
        mutable const child* Children;
        
        const ideal_key& child(M n) const override final;
        
        key(algebra<K, M> a, K k, const parent* const p):ideal_key(a, k, p), Children(nullptr) {}
        ~key() {
            delete Children;
        }
    };
    
    // child is a linked list that keeps track of all children generated from
    // a given key. 
    struct child : public parent {
        const key* const Child;
        const child* const Next;
        
        // child is able to search recursively down itself to find if
        // any keys have already been generated. 
        const child* const get(M n) const {
            if (this == nullptr) return nullptr;
            if (theory<K, M>::parent::Index == n) return this;
            return Next->get(n);
        }
        
        child(const key& p, const M index, const key* const c, const child* const n)
            : parent(p, index), Child(c), Next(n) {}
        ~child() {
            delete Next;
            delete Child;
        }
    };
    
    const key Master;
    virtual const key& master() const final override {
        return Master;
    };
    
public:
    heap(algebra<K, M> a, const K master) : Master(a, master) {}
    
    // TODO should implement move constructor. 
};
    
template<typename K, typename M>
const typename theory<K, M>::key& heap<K, M>::key::child(M n) const {
    // check the child keys to see if we've already generated this key. 
    const struct child* const z = Children->get(n);
    if (z != nullptr) return z->Key;
    
    // Derive the new key
    K derived = theory<K, M>::key::derive(n);
    
    // This will store the new key until it's passed off to the new child. 
    const key* const k;
    
    // if K is equal to the default constructor, then this is an error state.
    if (derived == K()) {
        // we use the zero key because it won't spawn new nodes. 
        k = new typename error_theory<K, M>::zero(theory<K, M>::key::Algebra, *this);
    } else {
        k = new typename heap<K, M>::key(theory<K, M>::key::Algebra, derived, *this);
    }
    
    // create a new child object
    Children = new heap<K, M>::child(*this, n, k, Children);
    
    return *k;
}

}

#endif 
