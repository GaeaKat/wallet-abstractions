#ifndef ABSTRACTIONS_ENCODINGS_UTF8_HPP
#define ABSTRACTIONS_ENCODINGS_UTF8_HPP

#include <abstractions/bytestring.hpp>
#include <abstractions/unicode.hpp>

namespace abstractions {
    
    namespace encoding {
        
        namespace utf8 {
            using string = vector<byte>;
            
            string write(unicode);
            
            unicode read(string str);
            
        }
        
    }
    
}

#endif
