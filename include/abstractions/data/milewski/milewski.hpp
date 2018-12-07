#ifndef MILEWSKI_DATA_RB_RB_HPP
#define MILEWSKI_DATA_RB_RB_HPP

#include <milewski/rb.hpp>
#include <milewski/Queue.h>
#include <abstractions/data/map.hpp>

namespace abstractions {
    
    namespace data {
        
        template <typename K, typename V>
        class rb_map {
            RBMap<K, V> Map;
            static const data::map::definition::map<rb_map, K, V> require_is_map{};
            
            rb_map(RBMap<K, V> m) : Map{m} {}
            
        public:
            V operator[](K k) const {
                return Map.findWithDefault(V{}, k);
            }
            
            rb_map insert(K k, V v) const {
                return RBMap<K, V>{m.inserted(k, v)};
            }
            
            bool contains(K k) const {
                return Map.member(k);
            }
            
            bool empty() {
                return Map.isEmpty();
            }
            
        };
        
        /*template <typename X>
        class lazy_queue {
            Queue<X> Q;
            
        public:
            
            bool empty() const {
                
            }
            
            const X& first() const {
                
            }
            
            lazy_queue<X> rest() const {
                
            }
            
            lazy_queue<X> operator+(X x) const {
                
            }
        };*/
        
    }
    
}

#endif

