#ifndef ABSTRACTIONS_DATA_HPP
#define ABSTRACTIONS_DATA_HPP

#include <abstractions/data/linked_list.hpp>
#include <data/tools/list_map.hpp>
#include <abstractions/data/milewski/milewski.hpp>
#include <data/map.hpp>
#include <data/tools/map_set.hpp>
#include <data/slice.hpp>

namespace abstractions
{

    template <typename X>
    using list = data::linked_list<X>;
            
    template <typename X>
    using slice = ::data::slice<X>;

    template <typename K, typename V>
    using list_map = ::data::list_map<K, V,
        list<::data::map::entry<K, V> >, ::data::list::iterator<list<::data::map::entry<K, V> >, ::data::map::entry<K, V> > >;
        
    template <typename K, typename V>
    using map = data::rb_map<K, V>;
    
    template <typename X>
    using set = data::map_set<map<X, bool>, X>;
        
    template <typename key, typename value, typename map>
    list<value> get_all(map m, list<key> k) {
        struct inner {
            map M;
                    
            inner(map m) : M{m} {}
                    
            list<value> operator()(key k, list<value> l) {
                value v = M[k];
                if (v == value{}) return l;
                return l + v;
            }
        };
                
        return reduce(inner{m}, k);
    }
    
}

#endif

