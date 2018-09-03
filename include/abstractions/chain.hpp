#ifndef ABSTRACTIONS_CHAIN_HPP
#define ABSTRACTIONS_CHAIN_HPP

#include <abstractions/data/set.hpp>
#include <abstractions/data/avl/avl.hpp>

namespace abstractions
{
    
    template <typename X>
    using set = data::set<X, data::trees::avl::node<X>>;
    
    template <typename X>
    using next = X (*const)(X);
    
    template <typename X>
    struct chain {
        next<X> Next;
        set<X> Last;
        
        chain<X> generate_new() const {
            if (Next == nullptr) return nullptr;
            if (Last == nullptr) return nullptr;
            
            return chain(Next, Last + Next(Last->First));
        }
        
        chain(next<X> n, set<X> s) : Next(n), Last(s) {}
        chain() : Last(), Next(nullptr) {}
    };
}

#endif
