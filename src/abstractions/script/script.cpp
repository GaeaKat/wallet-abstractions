#include <abstractions/script/script.hpp>

namespace abstractions {
    
    namespace script {
        bytes program::compile() const {
            std::vector<byte> b{static_cast<unsigned char>(length())};
            data::slice_ostream s{b};
            write(s);
            return b;
        };
    }
}
