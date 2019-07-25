// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_ABSTRACTIONS
#define ABSTRACTIONS_ABSTRACTIONS

#include <cstdint>
#include <memory>
#include <string>
#include <stdint.h>
#include <vector>
#include <data/list/linked_list.hpp>
#include <data/map.hpp>
#include <data/map/rb.hpp>
#include <data/tools/map_set.hpp>
#include <data/queue/functional_queue.hpp>
#include <data/math/number/bounded.hpp>
#include <data/slice.hpp>

#include <data/encoding/hex.hpp>
#include <data/encoding/ascii.hpp>

namespace abstractions {

    using N = unsigned long long int;

    const N all = N(0 - 1);

    const N aleph_0 = all / 2 + 1;
    
    inline const N plus(const N n, const N m) {
        return n + m;
    }

    using Z = const long long int;
    
    using satoshi = N;
    
    const satoshi empty = 0;
    
    using index = uint32_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    using int32 = int32_t;
    
    using uint160 = data::uint160;
    using uint256 = data::uint256;
    using uint512 = data::uint512;
    
    template <typename X>
    using vector = const std::vector<X>;

    using byte = uint8_t;
    
    using bytes = const vector<byte>;

    template<typename X>
    using pointer = std::shared_ptr<X>;

    using string = const std::string;
    using hex = data::encoding::hex::string;
    using ascii = data::encoding::ascii::string;

    using knowledge = const uint64_t; 
    
    using stringstream = std::stringstream;
    using istream = data::istream<byte>;
    using ostream = data::ostream<byte>;

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
