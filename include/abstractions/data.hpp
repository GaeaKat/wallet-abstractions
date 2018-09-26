#ifndef ABSTRACTIONS_DATA_HPP
#define ABSTRACTIONS_DATA_HPP

#include <abstractions/data/list.hpp>
#include <abstractions/data/set.hpp>
#include <abstractions/data/avl/map.hpp>

namespace abstractions
{

    template <typename X>
    using list = data::linked_list<X, pointer<X>>;

    template <typename X>
    using set = data::set<X, data::trees::avl::node<X>>;

    template <typename K, typename V>
    using map = data::avl_map<K, V>;
    
}

#endif

