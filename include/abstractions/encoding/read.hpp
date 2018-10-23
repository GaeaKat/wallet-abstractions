#ifndef ABSTRACTIONS_ENCODINGS_READ_HPP
#define ABSTRACTIONS_ENCODINGS_READ_HPP

namespace abstractions {

    namespace encodings {

        template <typename input_iterator, typename X>
        inline bool read(input_iterator i, input_iterator end, X& x) {
            if (i == end) return false;
            x = *i; i++;
            return true;
        }

    }

}

#endif
