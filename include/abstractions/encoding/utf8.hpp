#ifndef ABSTRACTIONS_ENCODINGS_UTF8_HPP
#define ABSTRACTIONS_ENCODINGS_UTF8_HPP

#include <abstractions/bytestring.hpp>
#include <abstractions/unicode.hpp>

namespace abstractions {
    
    namespace encoding {
        
        namespace utf8 {
            struct string : public vector<byte> {                
                string() {}
                string(N n) : vector<byte>(n) {}
            };
            
            string write(unicode);
            
            unicode read(string str);
            
        }
        
    }
    
}

#endif
