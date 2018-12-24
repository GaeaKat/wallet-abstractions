#ifndef ABSTRACTIONS_CONSTANT_HPP
#define ABSTRACTIONS_CONSTANT_HPP

namespace abstractions 
{

    template <typename X>
    struct constant {
        X Constant;
        
        template <typename Y>
        X operator()(Y) const {
            return Constant;
        }
    };

}

#endif

