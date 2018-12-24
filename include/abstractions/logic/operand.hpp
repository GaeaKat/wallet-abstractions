#ifndef ABSTRACTIONS_LOGIC_OPERAND_HPP
#define ABSTRACTIONS_LOGIC_OPERAND_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions {
    
    namespace statement {
    
        namespace operand {
            
            struct Equal {
                static const string symbol() {
                    return "=";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            struct Implies {
                static const string symbol() {
                    return "=>";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            struct And {
                static const string symbol() {
                    return "^";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            struct Or {
                static const string symbol() {
                    return "|";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            struct Plus {
                static const string symbol() {
                    return "+";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            struct Times {
                static const string symbol() {
                    return "*";
                }
                
                static const N precedence() {
                    return 0;
                }
            };
            
            template <typename op>
            string read() {
                return op::symbol();
            }
            
            template <typename op>
            string precedence() {
                return op::precedence();
            }
            
        }
    
    }
    
}

#endif
