#ifndef ABSTRACTIONS_ENDIAN_HPP
#define ABSTRACTIONS_ENDIAN_HPP

namespace abstractions {

    namespace endian {

        const uint16_t uint16_all = uint16_t(0) - uint16_t(1);

        const uint32_t uint32_all = uint32_t(0) - uint32_t(1);

        const uint16_t uint16_first_half = uint16_all << 8;
        const uint16_t uint16_second_half = uint16_all >> 8;

        const uint32_t uint32_first_half = uint32_all << 16;
        const uint32_t uint32_second_half = uint32_all >> 16;

        const uint32_t uint32_first_byte = uint32_first_half << 8;
        const uint32_t uint32_second_byte = uint32_first_byte >> 8;
        const uint32_t uint32_third_byte = uint32_second_byte >> 8;
        const uint32_t uint32_fourth_byte = uint32_second_byte >> 8;

        inline uint16_t reverse_bytes(uint16_t x) {
            return ((x & uint16_first_half) >> 8) + ((x & uint16_second_half) << 8);
        }

        inline uint32_t reverse_bytes(uint32_t x) {
            return ((x & uint32_first_byte) >> 24) + ((x & uint32_second_byte) >> 8) + ((x & uint32_third_byte) << 8) + ((x & uint32_fourth_byte) << 24);
        }

        namespace experiment {

            const unsigned int endianness_check_var = 1;

        }

        const bool Little = (*((char*)&experiment::endianness_check_var)) == experiment::endianness_check_var;

        const bool Big = !Little;

        enum endianness {
            big, 
            little
        };

        endianness Endianness = Little ? little : big;

        template <typename X>
        inline X to_or_from(endianness e, X x) {
            e == Endianness ? x : reverse_bytes(x); 
        }

        const uint16_t uint16_first_significant_byte = Big ? uint16_first_half : uint16_second_half;
        const uint16_t uint16_second_significant_byte = Big ? uint16_second_half : uint16_first_half;

        const uint32_t uint32_first_significant_byte = Big ? uint32_first_byte : uint32_fourth_byte;
        const uint32_t uint32_second_significant_byte = Big ? uint32_second_byte : uint32_third_byte;
        const uint32_t uint32_third_significant_byte = Big ? uint32_third_byte : uint32_second_byte;
        const uint32_t uint32_fourth_significant_byte = Big ? uint32_fourth_byte : uint32_first_byte;

    }

}

#endif 
