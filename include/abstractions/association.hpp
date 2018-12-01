#ifndef ABSTRACTIONS_ASSOCIATION_HPP
#define ABSTRACTIONS_ASSOCIATION_HPP

namespace abstractions
{
        
    template <typename K, typename V> 
    struct association {
        virtual const V operator[](K) const = 0;
        
        bool contains(K k) const {
            return this->operator[](k) != V{};
        }
    };
    
}

#endif
