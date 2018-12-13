#ifndef ABSTRACTIONS_ASSOCIATION_HPP
#define ABSTRACTIONS_ASSOCIATION_HPP

namespace abstractions
{
        
    template <typename K> 
    struct set {        
        virtual bool contains(K k) const = 0;
    };
    
    template <typename K, typename V> 
    struct association : public set<K> {
        virtual const V get(K) const = 0;
        
        bool contains(K k) const {
            return get(k) != V{};
        }
    };
    
}

#endif
