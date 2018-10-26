#ifndef ABSTRACTIONS_REDUCE_HPP
#define ABSTRACTIONS_REDUCE_HPP

#include "abstractions.hpp"
#include <abstractions/data.hpp>

namespace abstractions 
{

    template<typename V, typename K, typename R, typename L>
    R reduce(V value, R (*const plus)(K, R), L list) {
        if (list == L{}) {
            return R{};
        }
        
        return plus(value(data::list::first(list)), reduce(R{}, value, plus, data::list::rest(list)));
    }

}

#endif
