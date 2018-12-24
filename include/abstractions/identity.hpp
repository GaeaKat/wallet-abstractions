#ifndef ABSTRACTIONS_IDENTITY_HPP
#define ABSTRACTIONS_IDENTITY_HPP

namespace abstractions 
{

    template <typename X>
    struct identity {
        X operator()(X x) const {
        return x;
    };

}

#endif
