#ifndef ABSTRACTIONS_LOGIC_CONTRADICTION_HPP
#define ABSTRACTIONS_LOGIC_CONTRADICTION_HPP

#include <abstractions/logic/statement.hpp>
#include <exception>

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
    
    namespace statement {
        
        template<>
        struct reader<logic::contradiction> {
            string read() const {
                return "contradiction"; 
            }
        };
    
    }
    
    inline void contradiction() {
        return logic::contradiction::contradict("");
    }
    
}

#endif
