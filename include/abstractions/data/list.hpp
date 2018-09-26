#ifndef ABSTRACTIONS_DATA_LIST_HPP
#define ABSTRACTIONS_DATA_LIST_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions
{
    
    namespace data
    {
        
        namespace list {
        
            template <typename L, typename E>
            inline E first(const L l) {
                return l.first();
            }
                
            template <typename L>
            inline L rest(const L l) {
                return l.rest();
            }
            
            template <typename L>
            inline L append(const L l, const E elem) {
                return l.append(elem);
            }
            
            template <typename L, typename E>
            struct iterator {
                L List;
                
                iterator<L, E> operator++() {
                    return iterator{rest(List)};
                }
                
                E operator*() {
                    return first(List);
                }
                
                L* operator->() {
                    return &List;
                }
                
                // Operators == and != are required
                // but are implemented automatically. 
            };
            
        }
        
        template <typename X, typename Y> struct linked_list;
            
        template <typename X>
        struct node {
            X First;
            const linked_list<X, node<X>> Rest;
                
            node(X x, linked_list<X, node<X>> r) : First(x), Rest(r) {}
            node(X x) : First(x), Rest(nullptr) {}
                
            bool contains(X x) {
                if (x == First) return true;
                    
                return contains(Rest, x);
            }
                
        };
        
        // Now we say that a list containing elements of
        // type X is also a pointer to something of type Y. 
        template <typename X, typename Y>
        struct linked_list : pointer<Y> {                
            X first() const {
                if (*this == nullptr) return invalid<X>;
                    
                return this->First;
            };
                
            linked_list<X, Y> rest() const {
                if (*this == nullptr) return nullptr;
                        
                return this->Rest;
            };
            
            linked_list<X, Y> append(X x) const {
                return std::shared_ptr<Y>(std::make_shared(Y{x}));
            }
                
            linked_list<X, Y> operator+(X x) const {
                return append(x);
            }
                
            bool contains(X x) const {
                if (*this == nullptr) return false;
                
                if (this->First == x) return true;

                return this->Rest.contains(x);
            }
            
            bool operator==(linked_list<X, Y> l) {
                return first() == l.first() && rest() == l.rest();
            }
            
            linked_list(pointer<Y> py) : pointer<Y>(py) {}
            linked_list(Y* py) : pointer<Y>(py) {}
            linked_list() : pointer<Y>(nullptr) {}
            
            list::iterator<linked_list<X, Y>, X> begin() {
                return {*this};
            }
            
            list::iterator<linked_list<X, Y>, X> end() {
                return {};
            }
            
        };
        
    }
    
    template <typename X, typename Y>
    const data::linked_list<X, Y> zero<data::linked_list<X, Y>> = nullptr;
}

#endif

