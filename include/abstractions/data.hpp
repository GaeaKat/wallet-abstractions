// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABSTRACTIONS_DATA
#define ABSTRACTIONS_DATA

#include <data/list/linked_list.hpp>
#include <data/map.hpp>
#include <data/map/rb.hpp>
#include <data/tools/map_set.hpp>
#include <data/queue/functional_queue.hpp>
#include <data/slice.hpp>

namespace abstractions {

    template <typename X>
    using list = data::linked_list<X>;
            
    template <typename X>
    using slice = data::slice<X>;
        
    template <typename K, typename V>
    using map = data::rb_map<K, V>;
    
    template <typename X>
    using set = data::map_set<map<X, bool>, X>;
    
    template <typename X>
    using queue = data::functional_queue<list<X>>;
        
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
