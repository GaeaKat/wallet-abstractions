#ifndef ABSTRACTIONS_LOGIC_CONTRADICTION_HPP
#define ABSTRACTIONS_LOGIC_CONTRADICTION_HPP

#include <truth/statement/statement.hpp>
#include <exception>
#include <abstractions/fundamental.hpp>

namespace abstractions {

    namespace logic {
            
        // can only be constructed by being thrown. 
        class contradiction : std::exception {
            string What;
            contradiction(string w) : What{w} {}
                
        public:
            const char* what() const noexcept final override {
                return What.c_str();
            }
                
            static void contradict(string What) {
                throw contradiction{What};
            };
        };
        
    }
    
    inline void contradiction() {
        return logic::contradiction::contradict("");
    }
    
}

namespace truth {
    
    namespace statement {
        
        template<>
        struct writer<abstractions::logic::contradiction> {
            string write() const {
                return "contradiction"; 
            }
        };
    
    }
    
}

#endif
