#include <abstractions/keybook.hpp>

namespace abstractions
{
    template <typename K, typename tag>
    void add_all_address(std::map<tag, K>& m, vector<one_way<K, tag>> tags, set<K> keys) {
        if (keys == set<K>{}) return;
        
        if (valid(keys->First)) for (one_way<K, tag> f : tags) 
            m.insert(std::make_pair(f(keys->First), keys->First));
        
        add_all_address(m, tags, keys->Rest);
    }
    
    template <typename K, typename tag>
    map<tag, K> addresses(vector<one_way<K, tag>> tags, set<K> keys) {
        std::map<tag, K> m{};
        add_all_address(m, tags, keys);
        return m;
    }

}
