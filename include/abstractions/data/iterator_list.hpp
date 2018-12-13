#ifndef ABSTRACTIONS_DATA_ITERATOR_LIST_HPP
#define ABSTRACTIONS_DATA_ITERATOR_LIST_HPP

#include <abstractions/data/list.hpp>
#include <abstractions/association.hpp>

namespace abstractions
{
    
    namespace data
    {
        
        template <typename X, typename it>
        struct iterator_list {
            it Next;
            it End;
            
            bool empty() const {
                return Next == End;
            }
            
            // if the list is empty, then this function
            // will dereference a nullptr. It is your
            // responsibility to check. 
            const X& first() const {
                return *Next;
            }
            
            const iterator_list rest() const {
                if (empty()) return *this;
                
                return iterator_list{End, Next++};
            }
                
            iterator_list<X, it> operator+(X x) const {
                return append(x);
            }
                
            bool contains(X x) const {
                if (empty()) return false;
                
                Next->contains(x);
            }
            
            bool operator==(const iterator_list<X, it>& l) {
                if (this == &l) return true;
                return Next == l.Next && End == l.End;
            }
            
            iterator_list<X, it> from(N n) const {
                if (empty()) return nullptr;
                if (n == 0) return this;
                return rest().from(n - 1);
            }
            
            iterator_list(it n, it e) : Next{n}, End{e} {}
            
            it begin() {
                return Next;
            }
            
            it end() {
                return End;
            }
            
        };
        
    }

    template <typename X, typename it>
    inline bool empty(const data::iterator_list<X, it> l) {
        return l.empty();
    }

    template <typename X, typename it>
    inline const X& first(const data::iterator_list<X, it> l) {
        return l.first();
    }

    template <typename X, typename it>
    inline const data::iterator_list<X, it> rest(const data::iterator_list<X, it> l) {
        return l.rest();
    }

    template <typename X, typename it>
    inline const data::iterator_list<X, it> append(const data::iterator_list<X, it> l, const X elem) {
        return l.append(elem);
    }

}

#endif
