#ifndef ABSTRACTIONS_DATA_LIST_HPP
#define ABSTRACTIONS_DATA_LIST_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace data {
        
        namespace list {
            
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
