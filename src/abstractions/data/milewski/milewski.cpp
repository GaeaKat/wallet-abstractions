#include <abstractions/data/milewski/milewski.hpp>

namespace abstractions {
    
    namespace data {
        
        template <typename K, typename V>
        rb_map<K, V> std_pair_insert(rb_map<K, V> m, std::pair<K, V> e) {
            return map::insert(m, e.first, e.second);
        }
        
        template <typename K, typename V>
        rb_map<K, V>::rb_map(std::initializer_list<std::pair<K, V> > init) : Map{
            list::template reduce(std_pair_insert,
                iterator_list<std::pair<K, V>, std::pair<K, V>*>{init.begin(), init.end()})
        } {}
        
    }
    
}
