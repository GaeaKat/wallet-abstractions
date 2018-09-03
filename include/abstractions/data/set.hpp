#ifndef ABSTRACTIONS_TREES_SET_HPP
#define ABSTRACTIONS_TREES_SET_HPP

#include "tree.hpp"

namespace abstractions
{
    
    namespace data 
    {
    
        template <typename X, typename Y>
        struct set : public tree<X, Y>{
            virtual bool contains(X) const = 0;
            
            bool contains(set<X, Y> s) const;
            
            virtual set<X, Y> operator+(X) const = 0;
            virtual set<X, Y> operator-(X) const = 0;
            virtual set<X, Y> operator&(set<X, Y>) const = 0;
            virtual set<X, Y> operator|(set<X, Y>) const = 0;
            virtual set<X, Y> operator%(set<X, Y>) const = 0;
        };
    
    }
    
}

#endif
