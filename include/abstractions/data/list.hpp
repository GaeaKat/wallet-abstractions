#ifndef ABSTRACTIONS_DATA_LIST_HPP
#define ABSTRACTIONS_DATA_LIST_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace data {
        
        namespace list {
            
            // contains types that are used to define a list. 
            namespace definition
            {
                
                template <typename L>
                struct existence {
                    bool empty(L l) const {
                        return l.empty();
                    }
                    
                    N size(L l) const {
                        return l.size();
                    }
                };
                
                template <typename L>
                struct existence<L*> {
                    bool empty(L l) const {
                        return l == nullptr;
                    }
                    
                    N size(L l) const {
                        if (l == nullptr) return 0;
                        return l->size();
                    }
                };
                
                template <typename L>
                struct existence<pointer<L>> {
                    bool empty(L l) const {
                        return l == nullptr;
                    }
                    
                    N size(L l) const {
                        if (l == nullptr) return 0;
                        return l->size();
                    }
                };
                
                template <typename L, typename X>
                struct list : public existence<L> {
                    X& first(L l) const {
                        return l.first();
                    }
                    
                    L rest(L l) const {
                        return l.rest();
                    }
                };
                
                template <typename L, typename X>
                struct list<L*, X> : public existence<L*> {
                    X& first(L l) const {
                        return l->First;
                    }
                    
                    L rest(L l) const {
                        if (l == nullptr) return nullptr;
                        return l->rest();
                    }
                };
                
                template <typename L, typename X>
                struct list<pointer<L>, X> : public existence<pointer<L>> {
                    X& first(L l) const {
                        return l->First;
                    }
                    
                    L rest(L l) const {
                        if (l == nullptr) return nullptr;
                        return l->rest();
                    }
                };
                
                template <typename L, typename X>
                struct extendable : public list<L, X> {                
                    L append(L l, X x) const {
                        return l + x;
                    }
                };
                
                template <typename L, typename X>
                struct extendable<L*, X> : public list<L*, X> {
                    L append(L l, X x) const {
                        if (l == nullptr) return x;
                        return l->append(x);
                    }
                };
                
                template <typename L, typename X>
                struct extendable<pointer<L>, X> : public list<pointer<L>, X> {
                    L append(L l, X x) const {
                        if (l == nullptr) return x;
                        return l->append(x);
                    }
                };
                
            }
            
            template <typename L> 
            inline bool empty(L l) {
                return definition::existence<L>{}.empty(l);
            }
            
            template <typename L> 
            inline bool size(L l) {
                return definition::existence<L>{}.size(l);
            }
            
            template <typename L, typename X> 
            inline X& first(L l) {
                return definition::list<L, X>{}.first(l);
            }
            
            template <typename L, typename X> 
            inline L rest(L l) {
                return definition::list<L, X>{}.rest(l);
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
            to for_each(function f, from l) {
                if (empty(l)) return nullptr;
                return for_each(f, rest(l)) + f(*first(l));
            }
            
            template <typename function, typename from, typename to> 
            inline to for_each_indexed(N index, function f, from l) {
                if (empty(l)) return nullptr;
                return for_each_indexed(index + 1, f, rest(l)) + f(index, *first(l));
            }
            
            template <typename function, typename from, typename to> 
            inline to for_each_indexed(function f, from l) {
                return for_each_indexed(0, f, l);
            }
            
            template <typename function, typename list, typename value>
            value find(function satisfies, list l) {
                if (empty(l)) return value{};
                auto f0 = first(l);
                if (satisfies(f0)) return f0;
                return rest(l);
            }
            
            // this is an iterator that could go with a list. 
            template <typename L, typename E>
            struct iterator {
                L List;
                    
                iterator& operator=(iterator i) {
                        this->List = i.List;
                        return this;
                }
                    
                iterator& operator++() {
                        return operator=(iterator{rest(List)});
                }
                    
                E& operator*() {
                    return first(List);
                }
                        
                bool operator==(const iterator i) const {
                    List == i.List;
                }
                    
            };
            
            // This is a node that you could perhaps use to make a list. 
            template <typename X, typename Y>
            struct node {
                X First;
                Y Rest;
                        
                node(X x, Y r) : First(x), Rest(r) {}
                node(X x) : First(x), Rest{} {}
                    
                X first() const {
                        return First;
                }
                    
                Y rest() const {
                    return Rest;
                }
                        
                bool contains(X x) const {
                    if (x == First) return true;
                            
                    return contains(Rest, x);
                }
                    
                bool operator==(const node& n) const {
                    return First == n.First && Rest == n.Rest;
                }
                        
            };
        
        }
    
    }

}

#endif
