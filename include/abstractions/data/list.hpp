#ifndef ABSTRACTIONS_DATA_LIST_HPP
#define ABSTRACTIONS_DATA_LIST_HPP

#include <abstractions/invalid.hpp>

namespace abstractions
{
    
    namespace data
    {

        template <typename X, typename Y> struct list;
        
        template <typename X, typename Y>
        inline X first(list<X, Y> l) {
            if (l == nullptr) return invalid<X>;
                
            return l->First;
        }
            
        template <typename X, typename Y>
        inline list<X, Y> rest(list<X, Y> l) {
            if (l == nullptr) return nullptr;
                    
            return l->Rest;
        }
            
        template <typename X, typename Y>
        inline list<X, Y> append(const list<X, Y> l, X x) {
            return std::shared_ptr<Y>(std::make_shared(Y(x, l)));
        };
        
        template <typename X, typename Y>
        inline bool contains(const list<X, Y> l, X x) {
            if (l == nullptr) return false;
            
            return l->contains(x);
        }
        
        namespace lists
        {
            
            template <typename X>
            struct node {
                X First;
                const list<X, node<X>> Rest;
                
                node(X x, list<X, node<X>> r) : First(x), Rest(r) {}
                node(X x) : First(x), Rest(nullptr) {}
                
                bool contains(X x) {
                    if (x == First) return true;
                    
                    return contains(Rest, x);
                } 
                
            };
            
        }
        
        // Now we say that a list containing elements of
        // type X is also a pointer to something of type Y. 
        template <typename X, typename Y>
        struct list : pointer<Y> {                
            X first() const {
                return first(this);
            };
                
            list<X, Y> rest() const {
                return rest(this);
            };
                
            list<X, Y> operator+(X x) const {
                return append(this, x);
            }
                
            bool contains(X x) const {                
                return contains(this, x);
            }
                
        };
    
        // a set of list types that can be instantiated
        // using lists::node. But you could use all kinds of 
        // nodes. 
        template <typename X>
        using linked_list = list<X, lists::node<X>>;
        
    }
    
}

#endif

