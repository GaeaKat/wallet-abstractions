#ifndef ABSTRACTIONS_DATA_MAP_HPP
#define ABSTRACTIONS_DATA_MAP_HPP

namespace abstractions
{
    
    namespace data
    {
        
        namespace map
        {
            
            template <typename key, typename value>
            struct entry {
                key Key;
                value Value;
                        
                entry(key k, value v) : Key(k), Value(v) {}
                        
                // an invalid instance must exist for type value.
                entry(key k) : Key(k), Value{} {}
                        
                // Sorting is done with keys only. 
                bool operator<(entry<key, value> e) {
                    return Key < e.Key;
                }
                        
                bool operator==(entry<key, value> e) {
                    return Key == e.Key;
                }
                
                value operator[](key k) {
                    if (Key == k) return Value;
                    return value{};
                }
                
            };
            
        }
        
    }
    
}

#endif
