#ifndef ABSTRACTIONS_LOGIC_RELATION_HPP
#define ABSTRACTIONS_LOGIC_RELATION_HPP

#include <truth/statement/statement.hpp>
#include <abstractions/logic/operand.hpp>

namespace abstractions {
    
    namespace statement {
        
        template <typename A, typename R, typename B>
        struct relation {};
    
    }
    
}

namespace truth {
    
    namespace statement {

        template <typename A, typename R, typename B>
        struct writer<relation<A, R, B>> {
            string write() const {
                return "(" + statement::read<A>() + ") " + operand::read<R>() + " (" + statement::read<B>() + ")";
            }
        };
    
    }
    
}

#endif
