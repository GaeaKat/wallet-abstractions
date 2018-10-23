#ifndef ABSTRACTIONS_ENCODINGS_READ_HPP
#define ABSTRACTIONS_ENCODINGS_READ_HPP

namespace abstractions {
    
    namespace encodings {
        
        template <typename output_iterator, typename X>
        inline bool write(output_iterator i, output_iterator end, const X x) {
            if (i == end) return false;
            *i = x; i++;
            return true;
        }
            
    }
}

#endif 
