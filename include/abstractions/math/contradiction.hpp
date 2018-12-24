#ifndef ABSTRACTIONS_MATH_CONTRADICTION_HPP
#define ABSTRACTIONS_MATH_CONTRADICTION_HPP

#include <abstractions/abstractions.hpp>
#include <exception>

namespace abstractions {
    struct statement {
        virtual string state() const = 0;
    };
    
    // class that can only be constructed by being thrown. 
    class contradiction : std::exception {
        statement& What;
        contradiction(statement& w) : What{w} {}
        
    public:
        const char* what() const noexcept final override {
            return What.state().c_str();
        }
        
        static void contradict(statement& What) {
            throw contradiction{What};
        };
    };
    
    template <typename X> 
    struct equal {
        X Left;
        X Right;
        
        equal(X l, X r) : Left{l}, Right{r} {
            if (!(Left == Right)) contradiction::contradict(*this);
        }
    };
}

#endif
