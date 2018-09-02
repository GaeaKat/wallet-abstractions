#ifndef ABSTRACTIONS_KEYBOOK_HPP
#define ABSTRACTIONS_KEYBOOK_HPP

#include "claim.hpp"
#include "one_way.hpp"
#include "observe.hpp"
#include "set.hpp"
#include <tuple>

namespace abstractions
{
    
    template <typename K, typename tag>
    struct keybook {
        vector<one_way<K, tag>> Tags;
        
        const map<tag, K>& entries() const;
        
        virtual K get(tag t, one_way<K, tag> f) const {
            K k = entries()[t];
            return contains(Tags, f) && f(k) == t ? k : K{};
        }
        
        keybook(vector<one_way<K, tag>> t) : Tags(t) {}
    };
    
    // check whether a keybook is valid. 
    template <typename K, typename tag>
    bool valid(keybook<K, tag>& book) {
        const map<tag, K>& e = book.entries();
        for (tag t : e) for (one_way<K, tag> f : book.Tags) {
            K k = get(f, t);
            if (k != K{}) if (f(k) != t || e[t] != k) return false;
        }
        return true;
    };
    
    template <typename K, typename tag>
    map<tag, K> addresses(vector<one_way<K, tag>> Tags, set<K> keys);
    
    // This implementation of keybook caches results. 
    template <typename K, typename tag>
    class cached : public keybook<K, tag> {
        mutable std::map<std::tuple<tag, one_way<K, tag>>, K> keys;
    public:
        map<tag, K> Addresses;
        
        const map<tag, K>& entries() const final override {
            return Addresses;
        }
        
        K get(tag t, one_way<K, tag> f) const final override {
            K k = keys[std::tuple<tag, one_way<K, tag>>(t, f)];
            if (k != K{}) return k;
            
            k = keybook<K, tag>::get();
            if (k == K{}) return K{};
            keys.insert(std::make_pair(std::tuple<tag, one_way<K, tag>>(t, f), k));
            for (one_way<K, tag> f : keybook<K, tag>::Tags) if (f())
            return zero<K>;
        };
        
        cached(vector<one_way<K, tag>> t, set<K> keys) : keybook<K, tag>(t), Addresses(addresses(t, keys)) {}
        
        cached(vector<one_way<K, tag>> t, map<tag, K> a) : keybook<K, tag>(t), Addresses(a) {}
        
        cached(vector<one_way<K, tag>> t, map<tag, K> a, std::map<std::tuple<tag, one_way<K, tag>>, K> k)
            : keybook<K, tag>(t), keys(k), Addresses(a) {}
    };
    
    template <typename K, typename tag, typename script>
    K get_key(script s,
        const keybook<K, tag> n, 
        map<pattern<script>, tags<tag, script>> patterns) {
        for (pattern<script> match : patterns) if (match(s)) return n.get(patterns[match](s)); 
        return K{};
    }

}

#endif
