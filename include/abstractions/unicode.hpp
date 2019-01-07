#ifndef ABSTRACTIONS_UNICODE_HPP
#define ABSTRACTIONS_UNICODE_HPP

#include <string>
#include "fundamental.hpp"

namespace abstractions {
    
    struct unicode : public vector<uint32_t> {
        unicode();
        
        unicode(string s): vector<uint32_t>(s.size()) {
            for (int i = 0; i < s.size(); i++) this->at(i) = s[i];
        }
    };
}

#endif
