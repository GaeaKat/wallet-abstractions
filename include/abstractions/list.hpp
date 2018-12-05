#ifndef ABSTRACTIONS_LIST_HPP
#define ABSTRACTIONS_LIST_HPP

#include "abstractions.hpp"

namespace abstractions 
{
        
    namespace list
    {
            
        namespace definition
        {
            
            template <typename L, typename X>
            struct list {
                X& first(L l) {
                    return l.first();
                }
                
                L rest(L l) {
                    return l.rest();
                }
                
                bool empty(L l) {
                    return l.empty();
                }
            };
            
            template <typename L, typename X>
            struct list<L*, X> {
                X& first(L l) {
                    return l->First;
                }
                
                L rest(L l) {
                    return l->rest();
                }
                
                bool empty(L l) {
                    return l == nullptr;
                }
            };
            
            template <typename L, typename X>
            struct list<pointer<L>, X> {
                X& first(L l) {
                    return l->First;
                }
                
                L rest(L l) {
                    return l->rest();
                }
                
                bool empty(L l) {
                    return l == nullptr;
                }
            };
            
        }
    
        template<typename function, typename list, typename value>
        value reduce(function plus, list l) {
            if (empty(l)) return value{};
            
            return plus(value{first(l)}, reduce(plus, rest(l)));
        }
        
        template<typename list, typename value>
        value reduce(list l) {
            if (empty(l)) return value{};
            
            return value{first(l)} + reduce(plus, rest(l));
        }
            
        template <typename function, typename from, typename to> 
        to for_all(function f, from l) {
            if (empty(l)) return nullptr;
            return for_all(f, rest(l)) + f(*first(l));
        }
        
        template <typename function, typename from, typename to> 
        to map_indexed(N index, function f, from l) {
            if (empty(l)) return nullptr;
            return map_indexed(index + 1, f, rest(l)) + f(index, *first(l));
        }
        
        template <typename function, typename from, typename to> 
        inline to map_indexed(function f, from l) {
            return map_indexed(0, f, l);
        }
        
        template <typename function, typename list, typename value>
        value find(function satisfies, list l) {
            if (empty(l)) return value{};
            auto f0 = first(l);
            if (satisfies(f0)) return f0;
            return rest(l);
        }
        
    }

}

#endif
