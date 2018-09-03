#ifndef ABSTRACTIONS_TREES_MAP_HPP
#define ABSTRACTIONS_TREES_MAP_HPP

#include "tree.hpp"

namespace abstractions
{
    
    namespace data
    {
        
        namespace maps
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
                
            };
        
            template <typename X, typename Y, typename Z>
            struct map : public tree<maps::entry<X, Y>, Z> {
                Y operator[](X x){
                    // type Y must have an invalid value. 
                    if (this == nullptr) return invalid<Y>;
                    
                    if (x == this->Data.Key) return this->Data.Value;
                    
                    if (x < this->Data) return this->Left[x];
                    
                    return this->Right[x];
                }
                
            };
            
        }
        
    }
    
}

#endif
