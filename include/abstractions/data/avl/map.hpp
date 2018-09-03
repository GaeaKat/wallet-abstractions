#ifndef ABSTRACTIONS_TREES_AVL_MAP_HPP
#define ABSTRACTIONS_TREES_AVL_MAP_HPP

#include <abstractions/data/map.hpp>
#include "avl.hpp"

namespace abstractions
{
    
    namespace data 
    {
        
        template <typename K, typename V>
        using avl_map = maps::map<K, V, trees::avl::node<maps::entry<K, V>>>;
        
    }
    
}

#endif

