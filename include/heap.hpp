#ifndef HD_HEAP_HPP
#define HD_HEAP_HPP

#include "hd.hpp"

namespace hd_tools
{

// Implementation of theory which stores all data
// generated on the heap and releases the memory upon
// distruction of the entire class. should be suitable
// for most purposes, but you could also have a much
// more intelligent implementation that had a database
// and automatic memory management and so on. 
template<typename K, typename M>
class heap final : public error_theory<K, M> {    
    typedef typename theory<K, M>::key ideal_key;
    typedef typename theory<K, M>::parent parent;
    
    struct key;
    
    // child is a linked list that keeps track of all children generated from
    // a given key. 
    struct child_node final : public parent {
        const key* const Child;
        const child_node* const Next;
        
        // child is able to search recursively down itself to find if
        // any keys have already been generated. 
        const child_node* const get(M n) const {
            if (theory<K, M>::parent::Index == n) return this;
            if (Next == nullptr) return nullptr;
            return Next->get(n);
        }
        
        child_node(const key& p, const M index, const key* const c, const child_node* const n)
            : parent(p, index), Child(c), Next(n) {}
        ~child_node() {
            delete Next;
            delete Child;
        }
        
        list<K> children(const child_node* const k);
    };
    
    struct key final : public ideal_key {
        // mutable because adding childen does not change the key 
        // as it is seen publicly. 
        mutable const child_node* Children;
        
        const ideal_key& child(M n) const override final;
        
        key(algebra<K, M> a, K k, const parent* const p):ideal_key(a, k, p), Children(nullptr) {}
        ~key() {
            delete Children;
        }
        
        // I think we need this if we want a function that returns a new heap
        // object. 
        key(key&& k) : ideal_key(k.Algebra, k.Key, k.Parent), Children(k.Children) {
            k.Children = nullptr;
        }
        
        list<K> children() {
            return new node<K>(theory<K, M>::key::Key, children(Children));
        }
    };
    
    const key Master;
    virtual const key& master() const final override {
        return Master;
    };
    
    list<K> children(const child_node* const k) {
        if (k == nullptr) return nullptr;
        
        return k->children();
    }
    
public:
    heap(algebra<K, M> a, K master) : Master(a, master, nullptr) {}
    
    // can get a list of all keys generated. 
    list<K> keys() {
        return Master.children();
    }
};

template<typename K, typename M>
list<K> heap<K, M>::child_node::children(const child_node* const k) {
    if (Child == nullptr) return nullptr;
            
    return Child->children();
}
    
template<typename K, typename M>
const typename theory<K, M>::key& heap<K, M>::key::child(M n) const {
    // check the child keys to see if we've already generated this key. 
    const struct child_node* const z = Children->get(n);
    if (z != nullptr) return z->Key;
    
    // Derive the new key
    K derived = theory<K, M>::key::derive(n);
    
    // This will store the new key until it's passed off to the new child. 
    const key* k;
    
    // if K is equal to the default constructor, then this is an error state.
    if (derived == K()) {
        // we use the zero key because it won't spawn new nodes. 
        k = new typename error_theory<K, M>::zero(theory<K, M>::key::Algebra, *this);
    } else {
        k = new typename heap<K, M>::key(theory<K, M>::key::Algebra, derived, *this);
    }
    
    // create a new child object
    Children = new heap<K, M>::child_node(*this, n, k, Children);
    
    return *k;
}

}

#endif 
