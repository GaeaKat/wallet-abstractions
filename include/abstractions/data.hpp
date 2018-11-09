#ifndef ABSTRACTIONS_DATA_HPP
#define ABSTRACTIONS_DATA_HPP

#include <abstractions/data/list.hpp>
#include <abstractions/data/set.hpp>
#include <abstractions/data/tree.hpp>
#include <abstractions/data/map.hpp>

namespace abstractions
{

    template <typename X>
    using list = data::linked_list<X, data::list::node<X> >;

    template <typename X>
    using set = data::set<X, data::trees::node<X> >;

    template <typename K, typename V>
    using map = data::map<K, V, data::trees::node<data::maps::entry<K, V> > >;
    
}

#endif

