#ifndef ABSTRACTIONS_ASSOCIATION_HPP
#define ABSTRACTIONS_ASSOCIATION_HPP

#include <abstractions/data/map.hpp>

namespace abstractions
{
        
    template <typename K> 
    class abstract_set {
    public:
        virtual bool contains(K k) const = 0;
    };
    
    template <typename K, typename V> 
    class association : abstract_set<K> {
    public:
        virtual const V get(K) const = 0;
        
        const V operator[](K k) const {
            return get(k);
        }
        
        bool contains(K k) const override {
            return get(k) != V{};
        }
    };
    
    template <typename K, typename V> 
    class abstract_map : association<K, V> {
    public:
        // proof that this abstract class implements map. 
        using is_map = data::map::definition::map<abstract_map<K, V>*, K, V>;
        using is_removable = data::map::definition::removable<abstract_map<K, V>*, K>;
        static is_map requirement1{};
        static is_removable requirement2{};
        
        virtual const V get(K) const = 0;
        
        virtual abstract_map* insert(K k, V v) const = 0;
        
        virtual abstract_map* remove(K k) const = 0;
    };
    
}

#endif
