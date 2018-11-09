#ifndef ABSTRACTIONS_SLICE_HPP
#define ABSTRACTIONS_SLICE_HPP

#include "abstractions.hpp"

namespace abstractions
{
    
    template <typename X>
    class slice {
        mutable X invalid;
        const X* data;
        uint64_t len; 
            
    public:
        const N size() const {
            return len;
        }
            
        const X& operator[](N n) const {
            if (n >= len) return invalid;
            return data[n];
        }
            
        slice() : invalid(0), data(nullptr), len(0) {};
        
        slice(vector<X> v) : invalid(0), data(v.data()), len(v.size()) {};
            
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
        
        class iterator {
            using iterator_category = std::input_iterator_tag;
            using value_type = X&;
                
            slice<X> Slice;
            uint64_t Index;
            
            iterator(slice<X> s, N n) : Slice(s), Index(n) {}
            
            friend class slice;
            
        public:
            
            X& operator*() const {
                if (Index >= Slice.size()) return Slice.invalid;
            }

            X& operator++() {
                Index ++;
                return *this;
            }
            
            X& operator+=(N n) {
                Index += n;
                return *this;
            }
                
            bool operator==(const X& x) const {
                this->operator*() == x;
            }
                
            bool operator!=(const X& x) const {
                this->operator*() != x;
            }
                
            bool operator==(const iterator i) const {
                this->operator*() == *i;
            }
                
            bool operator!=(const iterator i) const {
                this->operator*() != *i;
            }
            
            iterator& operator=(iterator i) {
                Slice = i.Slice;
                Index = i.Index;
                return *this;
            }
            
            slice<X> next(N n) {
                if (n == 0) return slice<X>();
                slice<X> s = Slice.range(Index, Index += n);
            }
        };

        iterator begin() const {
            return iterator(*this, N(0));
        }
            
        iterator end() const {
            return iterator(*this, size());
        }
            
    };

}

#endif

