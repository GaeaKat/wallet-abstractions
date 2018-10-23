#ifndef ABSTRACTIONS_ENDIAN_HPP
#define ABSTRACTIONS_ENDIAN_HPP

namespace abstractions {
    
    namespace endian {
        
        namespace check {
    
            const unsigned int entry = 1;
            
        }
    
        const bool little = (*((char*)&check::entry)) == check::entry;
        
        const bool big = !little;
    
    }

}

#endif 
