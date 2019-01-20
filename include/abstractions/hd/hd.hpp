#ifndef ABSTRACTIONS_HD_HD_HPP
#define ABSTRACTIONS_HD_HD_HPP

#include <stdint.h>
#include <vector>
#include <string>
#include <abstractions/hd/bip32.hpp>

namespace abstractions {

    // Namsepace hd contains types related to the management of 
    // heirarchical deterministic keys. 
    namespace hd {

        // abstract class containing the theory of hd key derivation.
        template<typename K>
        struct tree {
            struct parent;
            
            // Key takes any type K and attaches some extra data
            // that keeps track of where it is in the heirarchy. 
            class key {
                bip32::algebra<K> Algebra;
            public:
                K Key;
                
                // this key knows how to derive new objects of type K.
                K derive(bip32::child_index m) const {
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
                virtual const key& child(bip32::child_index n) const = 0;
                
                const key& operator^(bip32::child_index n) const {
                    return child(n);
                }
                
                // Keys are equal if they have equal K types, even
                // if they were derived in a different way. 
                bool operator==(const key& x) const {
                    return Key == x.Key;
                }
                
                // an implementation and object of type K must exist for a key
                // to exist, but alone they are not sufficient. 
                key(bip32::algebra<K> a, K k, const parent* const p) : Algebra(a), Key(k), Parent(p) {}
                virtual ~key() {}
            };
            
            // parent connects a key to its parent and tells
            // how the key was derived from the parent. 
            struct parent {
                const key& Key;
                bip32::child_index Index;
                
                // may be overrided to provide for error cases.
                virtual const std::string* const error() const {
                    return nullptr;
                }
                
                parent(const key& key, bip32::child_index index) : Key(key), Index(index) {}
                virtual ~parent() {}
            };

            // every implementation must have a master key. 
            virtual const key& master() const = 0;
            
            // Given any derivation, generate the key which
            // results from that derivation. 
            const key& derive(bip32::derivation d) {
                key* const r = master();
                
                for(auto i = d.begin(); i != d.end(); ++i) {
                    r = r->child(*i);
                }
                
                return *r;
            }
            
            virtual ~theory() {}
        };

    }

}

#endif
