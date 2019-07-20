#include <abstractions/script/script.hpp>

namespace abstractions::script {
        extern const boost::endian::order ENDIANESS=boost::endian::order::native;
        bytes program::compile() const {
            std::vector<byte> b{static_cast<unsigned char>(length())};
            data::slice_writer s{b,ENDIANESS};
            write(s);
            return b;
        };
    }
