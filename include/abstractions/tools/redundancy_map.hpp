#ifndef ABSTRACTIONS_TOOLS_REDUNDANCY_MAP_HPP
#define ABSTRACTIONS_TOOLS_REDUNDANCY_MAP_HPP

#include <abstractions/inverse.hpp>
#include <data/map.hpp>

namespace abstractions {
    
    // implementation of map which keeps track of things by inverse function.
    template <typename F, typename M, typename key, typename value>
    struct redundancy_map {
        static const data::map::definition::map<M, key, value> M_is_key_value_map{};
        static const data::map::definition::map<redundancy_map, key, inverse::proof<F, key, value>> redundancy_map_is_key_inverse_proof_map{};
        
        F Function;
        
        M Map;
        
        bool empty() const {
            return Map.empty();
        }
        
        inverse::proof<F, key, value> operator[](key k) {
            return inverse::prove(Function, k, Map[k]);
        }
        
        redundancy_map insert(key k, inverse::proof<F, key, value> p) {
            if (k != p.SuchThat && p.Exist.Function != Function) return {};
            return {Function, Map.insert(k, p)};
        }
        
        redundancy_map insert(key k) {
            return {Function, Map.insert(k, Function(k))};
        }
        
        redundancy_map remove(key k) {
            return {Function, Map.remove(k)};
        }
        
    };
    
}

#endif
