#ifndef ABSTRACTIONS_DATA_HPP
#define ABSTRACTIONS_DATA_HPP

#include <abstractions/data/linked_list.hpp>
#include <abstractions/data/list_map.hpp>
#include <abstractions/slice.hpp>

namespace abstractions
{

    template <typename X>
    using list = data::linked_list<X>;
    
    template <typename X>
    using set = list<X>;
    
    template <typename X>
    bool subset(set<X> a, set<X> b);

    template <typename K, typename V>
    using map = data::list_map<K, V,
        list<data::map::entry<K, V> >, data::list::iterator<list<data::map::entry<K, V> >, data::map::entry<K, V> > >;
    
}

#endif

