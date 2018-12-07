#ifndef ABSTRACTIONS_SLICE_HPP
#define ABSTRACTIONS_SLICE_HPP

#include <abstractions/data/list.hpp>

namespace abstractions
{

    template <typename X>
    class slice {
        mutable X invalid;
        X* data;
        uint64_t len; 
            
    public:
        const N size() const {
            return len;
        }
            
        X& operator[](N n) const {
            if (n >= len) return invalid;
            return data[n];
        }
            
        slice() : invalid(0), data(nullptr), len(0) {};
        
        slice(vector<X>& v) : invalid(0), data(v.data()), len(v.size()) {};
            
        slice<X> range(N begin, N end) {
            if (begin >= len || end >= len || begin >= end) return slice();
            
            return slice(data[begin], end - begin);
        };
        
        slice& operator=(slice<X> s) {
            invalid = s.invalid;
            data = s.data;
            len = s.len;
            return *this;
        }
        
        bool operator==(const slice<X>& s) const {
            if (this == &s) return true;
            if (data == s.data && len == s.len) return true;
            return false;
        }
        
        struct list {
            slice<X>& Slice;
            N Index;
            
            list& operator=(list i) {
                Slice = i.Slice;
                Index = i.Index;
                return *this;
            }
            
            bool empty() const {
                return Index >= Slice.size();
            }
            
            X& first() const {
                if (empty()) return Slice.invalid;
                
                return Slice[Index];
            }
            
            list rest() const {
                if (empty()) return *this;
                
                return {Slice, Index + 1};
            }
        
            bool operator==(const list& s) const {
                return Slice == s.Slice && (Index == s.Index || (empty() && s.empty()));
            }
            
            list(slice<X>& s, N n) : Slice(s), Index(n) {}
        };

        data::list::iterator<list, X> begin() {
            return data::list::iterator<list, X>{list{*this, N(0)}};
        }
            
        data::list::iterator<list, X> end() {
            return data::list::iterator<list, X>{list{*this, size()}};
        }
            
    };
                
    template <typename X>
    inline bool empty(const typename slice<X>::list l) {
        return l.empty();
    }
                
    template <typename X>
    inline X& first(const typename slice<X>::list l) {
        return l.first();
    }
                
    template <typename X>
    inline const typename slice<X>::list rest(const typename slice<X>::list l) {
        return l.rest();
    }

}

#endif

