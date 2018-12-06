#ifndef ABSTRACTIONS_MAP_HPP
#define ABSTRACTIONS_MAP_HPP

#include <abstractions/list.hpp>

namespace abstractions
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
            
        namespace definition
        {
                
            template <typename M>
            struct existence {
                bool empty(M m) {
                    return m.empty();
                }
            };
                
            template <typename M>
            struct existence<M*> {
                bool empty(M m) {
                    return m == nullptr;
                }
            };
                
            template <typename M>
            struct existence<pointer<M>> {
                bool empty(M m) {
                    return m == nullptr;
                }
            };
                
            // functions relating to maps which to not require
            // knowledge of the value type. 
            template <typename M, typename key>
            struct set : public existence<M> {
                bool contains(M m, key k) {
                    return m.contains(k);
                }
            };
                
            // specialization for pointer types. 
            template <typename M, typename key>
            struct set<M*, key> : public existence<M*> {
                bool contains(M m, key k) {
                    return m->contains(k);
                }
            };
                
            // specialization for pointer types. 
            template <typename M, typename key>
            struct set<pointer<M>, key> : public existence<pointer<M>> {
                bool contains(M m, key k) {
                    return m->contains(k);
                }
            };
                
            // functions relating to maps which to not require
            // knowledge of the value type. 
            template <typename M, typename key>
            struct removeable : public set<M, key> {
                M remove(M m, key k) {
                    return m.remove(k);
                }
            };
                
            // specialization for pointer types. 
            template <typename M, typename key>
            struct removeable<M*, key> : public set<M*, key> {
                M remove(M m, key k) {
                    return m->remove(k);
                }
            };
                
            // specialization for pointer types. 
            template <typename M, typename key>
            struct removeable<pointer<M>, key> : public set<pointer<M>, key> {
                M remove(M m, key k) {
                    return m->remove(k);
                }
            };
        
            // Now we're getting to something that actually looks more like a map.
            template <typename M, typename key, typename value>
            struct map : public set<M, key> {
                value get(M m, key k) {
                    return m[k];
                }
                    
                M insert(M m, key k, value v) {
                    return m.insert(k, v);
                }
            }; 
        
            template <typename M, typename key, typename value>
            struct map<M*, key, value> : public set<M*, key> {
                value get(map m, key k) {
                    return m->get(k);
                }
                    
                map insert(map m, key k, value v) {
                    return m->insert(k, v);
                }
            }; 

            template <typename M, typename key, typename value>
            struct map<pointer<M>, key, value> : public set<pointer<M>, key> {
                value get(M m, key k) {
                    return m->get(k);
                }
                    
                M insert(M m, key k, value v) {
                    return m->insert(k, v);
                }
            }; 

            // For some kinds of maps, it's possible to count over
            // all the elements, in which case the map can be treated
            // as a list of entries. 
            template <typename M, typename key, typename value, typename L>
            struct countible : public map<M, key, value> {
                L entries(M m) {
                    static const abstractions::list::definition::list<L, entry<key, value>> requirement{};
                    return m.entries();
                }
            }; 

            template <typename M, typename key, typename value, typename L>
            struct countible<M*, key, value, L> : public map<M*, key, value> {
                L entries(M m) {
                    static const abstractions::list::definition::list<L, entry<key, value>> requirement{};
                    return m->entries();
                }
            }; 

            template <typename M, typename key, typename value, typename L>
            struct countible<pointer<M>, key, value, L> : public map<pointer<M>, key, value> {
                L entries(M m) {
                    static const abstractions::list::definition::list<L, entry<key, value>> requirement{};
                    return m->entries();
                }
            }; 

        }

        // functions that can be satisfied by maps. 
        template <typename M>
        inline bool empty(M m) {
            return definition::existence<M>{}.empty(m);
        }

        template <typename M, typename K, typename V> 
        inline V get(M m, K k) {
            return definition::map<M, K, V>{}.get(m, k);
        }

        template <typename M, typename K, typename V> 
        inline M insert(M m, K k, V v) {
            return definition::map<M, K, V>{}.insert(m, k, v);
        }

        template <typename M, typename K> 
        inline bool contains(M m, K k) {
            return definition::set<M, K>{}.contains(m, k);
        }

        template <typename M, typename K> 
        inline M remove(M m, K k) {
            return definition::removeable<M, K>{}.remove(m, k);
        }
        
    }
    
}

#endif
