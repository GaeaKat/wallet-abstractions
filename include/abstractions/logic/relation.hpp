#ifndef ABSTRACTIONS_LOGIC_RELATION_HPP
#define ABSTRACTIONS_LOGIC_RELATION_HPP

#include <abstractions/logic/statement.hpp>
#include <abstractions/logic/operand.hpp>

namespace abstractions {
    
    namespace statement {
        
        template <typename A, typename R, typename B>
        struct relation {};
            
        template <typename A, typename R, typename B>
        struct reader<relation<A, R, B>> {
            string read() const {
                return "(" + statement::read<A>() + ") " + operand::read<R>() + " (" + statement::read<B>() + ")";
            }
        };
    
    }
    
}

#endif
