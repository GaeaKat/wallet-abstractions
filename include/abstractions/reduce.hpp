#ifndef ABSTRACTIONS_REDUCE_HPP
#define ABSTRACTIONS_REDUCE_HPP

#include "abstractions.hpp"
#include <abstractions/data.hpp>

namespace abstractions 
{

    template<typename K, typename R, typename L>
    R reduce(R (*const value)(K), R (*const plus)(K, R), L list) {
        if (list == nullptr) {
            return zero<R>;
        }
        
        return plus(value(data::first(list)), reduce(invalid<R>, value, plus, data::rest(list)));
    }

}

#endif
