#ifndef ABSTRACTIONS_OPERATION_HPP
#define ABSTRACTIONS_OPERATION_HPP

namespace abstractions 
{

    template <typename X, typename Y>
    struct operation {
        X Function;
        Y Argument;
                
        template <typename L, typename Z>
        L operator()(Z z) {
            return Function(z)(Argument(z));
        }
    };

}

#endif
