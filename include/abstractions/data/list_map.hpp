#ifndef ABSTRACTIONS_DATA_LIST_MAP_HPP
#define ABSTRACTIONS_DATA_LIST_MAP_HPP

#include <abstractions/data/list.hpp>
#include <abstractions/data/map.hpp>

namespace abstractions {
    
    namespace data {
        
        // any list type can be turned into a map type. 
        template <typename key, typename value, typename list, typename it>
        struct list_map {
            list List;
            
            bool empty() const {
                return List.empty();
            }
            
            data::map::entry<key, value>& first() const {
                return List.first();
            }

            list_map rest() {
                return list_map{List.rest()};
            }
            
            value operator[](key k) const {
                if (empty()) return value{};
                
                value v = first()[k];
                
                if (v != value{}) return v;
                
                return list_map{rest(List)}[k];
            }
            
            it begin() const {
                return List.begin();
            }
            
            it end() const {
                return List.end();
            }
            
            list_map(list l) : List(l) {}
        };
        
    }
                
    template <typename key, typename value, typename list, typename it>
    inline bool empty(const data::list_map<key, value, list, it> l) {
        return l.empty();
    }
                
    template <typename key, typename value, typename list, typename it>
    inline const data::map::entry<key, value>& first(const data::list_map<key, value, list, it> l) {
        return l.first();
    }
                
    template <typename key, typename value, typename list, typename it>
    inline const data::list_map<key, value, list, it> rest(const data::list_map<key, value, list, it> l) {
        return l.rest();
    }
            
    template <typename key, typename value, typename list, typename it>
    inline const data::list_map<key, value, list, it> append(const data::list_map<key, value, list, it> l, const data::map::entry<key, value> elem) {
        return data::list_map<key, value, list, it>{append(l.List, elem)};
    }

}

#endif
