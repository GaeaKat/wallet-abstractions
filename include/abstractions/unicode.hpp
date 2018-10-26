#ifndef ABSTRACTIONS_UNICODE_HPP
#define ABSTRACTIONS_UNICODE_HPP

#include <string>

namespace abstractions {
    
    struct unicode : public vector<uint32_t> {
        unicode();
        
        unicode(string);
    };
}

#endif
