#ifndef HD_HD_HPP
#define HD_HD_HPP

#include <stdint.h>
#include <vector>
#include <string>
#include "algebra.hpp"

// Namsepace hd contains types related to the management of 
// heirarchical deterministic keys. 
namespace hd
{

// A representation of a chain of operations which create a
// particular key. 
template<typename M>
using derivation = std::vector<M>;

// abstract class containing the theory of hd key derivation.
template<typename K, typename M>
struct theory {
    struct parent;
    
    // Key takes any type K and attaches some extra data
    // that keeps track of where it is in the heirarchy. 
    class key {
        algebra<K, M> Algebra;
    public:
        K Key;
        
        // this key knows how to derive new objects of type K.
        K derive(M m) const {
            return Algebra(Key, m);
        }
        
        // pointer to the parent key from which this key was derived.
        // not required to be non-null, but the memory it points to
        // is required to be managed by the implementation. 
        // 
        // The heap implementation that comes with this library
        // provides the full history through this pointer. 
        const parent* const Parent;
        
        // Only implementations know how to create objects of type key&. 
        virtual const key& child(M n) const = 0;
        
        // Keys are equal if they have equal K types, even
        // if they were derived in a different way. 
        bool operator==(const key& x) const {
            return Key == x.Key;
        }
        
        // an implementation and object of type K must exist for a key
        // to exist, but alone they are not sufficient. 
        key(algebra<K, M> a, K k, const parent* const p) : Algebra(a), Key(k), Parent(p) {}
        virtual ~key() {}
    };
    
    // parent connects a key to its parent and tells
    // how the key was derived from the parent. 
    struct parent {
        const key& Key;
        M Index;
        
        // may be overrided to provide for error cases.
        virtual const std::string* const error() const {
            return nullptr;
        }
        
        parent(const key& key, M index) : Key(key), Index(index) {}
        virtual ~parent() {}
    };

    // every implementation must have a master key. 
    virtual const key& master() const = 0;
    
    // Given any derivation, generate the key which
    // results from that derivation. 
    const key& derive(derivation<M> d) {
        key* const r = master();
        for(M i : d) {
            r = r->child(i);
        }
        
        return *r;
    }
    
    virtual ~theory() {}
};

// in the case that the key type K has a default constructor,
// can use this for error states. 
template<typename K, typename M>
struct error_theory : public theory<K, M> {
    typedef typename theory<K, M>::key key;
    typedef typename theory<K, M>::parent ideal_parent;
    
    struct zero final : public key {
        // objects of type zero simply return themselves
        // for any possible derivation. 
        const key& child(M n) const {
            return *this;
        }
        
        zero(algebra<K, M> a, const ideal_parent* const p) : key(a, K(), p) {}
    };
    
    struct parent : ideal_parent {
        const std::string* const Error;
        
        const std::string* const error() const final override {
            return Error;
        }
        
        parent(const key& p, M index, const std::string* const err) : ideal_parent(p, index), Error(err) {}
        parent(const key& p, M index) : ideal_parent(p, index), Error(nullptr) {}
        
        // the underlying implementation is considered to be responsible for whatever Error
        // points to, so we don't delete it. 
        ~parent() {}
    };
    
    virtual ~error_theory() {}
};

}

#endif
