#ifndef ABSTRACTIONS_LOGIC_STATEMENT_HPP
#define ABSTRACTIONS_LOGIC_STATEMENT_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace statement {
        
        template <typename statement> struct reader;
        
        template <typename X>
        struct reader<X&> {
            string read() const {
                return reader<X>{}.read();
            }
        };
        
        template <typename X>
        struct reader<X*> {
            string read() const {
                return reader<X>{}.read();
            }
        };
        
        template <typename statement>
        string read() {
            reader<statement>{}.read();
        }
    
    }
    
}

#endif
