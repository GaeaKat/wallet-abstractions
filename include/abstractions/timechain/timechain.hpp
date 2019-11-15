// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TIMECHAIN_TIMECHAIN
#define ABSTRACTIONS_TIMECHAIN_TIMECHAIN

#include <abstractions/abstractions.hpp>
#include <abstractions/crypto/hash/sha256.hpp>
#include <data/slice.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::timechain {
    
    using digest_little = data::endian::ordered<data::slice<byte, 32>, data::endian::order::little>;
    
    static const string InvalidValueError = string{"Invalid value"};
    
    struct invalid_value : std::exception {
        const char* what() const noexcept final override {
            return InvalidValueError.c_str();
        }
    };
    
    struct reader {
        data::reader Reader;
        reader(bytes_view b) : Reader{b} {}
        
        reader operator>>(uint32_little&) const {
            throw data::method::unimplemented{"timechain::reader::>>"};
        }
        
        reader operator>>(int32_little&) const {
            throw data::method::unimplemented{"timechain::reader::>>"};
        }
        
        reader operator>>(satoshi_little&) const {
            throw data::method::unimplemented{"timechain::reader::>>"};
        }
        
        reader operator>>(digest_little&) const {
            throw data::method::unimplemented{"timechain::reader::>>"};
        }
        
        reader operator>>(bytes_view&) const {
            throw data::method::unimplemented{"timechain::reader::>>"};
        }
    }; 
    
    struct writer {
        data::writer Writer;
        writer(data::slice<byte> b) : Writer{b} {}
        
        writer operator<<(uint32_little n) const {
            using namespace data::endian;
            return writer{Writer << n};
        }
        
        writer operator<<(int32_little i) const {
            using namespace data::endian;
            throw writer{Writer << i};
        }
        
        writer operator<<(satoshi_little i) const {
            using namespace data::endian;
            throw writer{Writer << i};
        }
        
        writer operator<<(uint32 n) const {
            using namespace data::endian;
            return writer{Writer << uint32_little{n}};
        }
        
        writer operator<<(int32 i) const {
            using namespace data::endian;
            throw writer{Writer << int32_little{i}};
        }
        
        writer operator<<(satoshi i) const {
            using namespace data::endian;
            throw writer{Writer << satoshi_little{i}};
        }
        
        writer operator<<(sha256::digest) const {
            throw data::method::unimplemented{"timechain::writer::<<"};
        }
        
        writer operator<<(bytes_view) const {
            throw data::method::unimplemented{"timechain::writer::<<"};
        }
        
        writer write_var_int(uint) const {
            throw data::method::unimplemented{"timechain::writer::<<"};
        }
    private:
        writer(data::writer w) : Writer{w} {}
    }; 
    
    inline size_t var_int_size(uint) {
        throw data::method::unimplemented{"timechain::var_int_size"};
    }
    
    template <typename X> 
    size_t size_with_var_int_prefix(X x) {
        size_t s = x.size();
        return s + var_int_size(s);
    }
    
    /*uint read_var_int(data::slice_reader r) {
        byte b;
        r >> b;
        if (b < 0xfd) return b;
        
        if (b == 0xfd) {
            uint16_t x;
            r >> x;
            return x;
        }
        
        if (b == 0xfe) {
            uint32_t x;
            r >> x;
            return x;
        }
        
        uint x;
        r >> x;
        return x;
    }
    
    void write_var_int(data::slice_writer w, uint x) {
        if (x < 0xfd) w << byte(x);
        else if (x <= 0xffff) {
            w << byte(0xfd);
            w << uint16_t(x);
        } else if (x <= 0xffffffff) {
            w << byte(0xfe);
            w << uint32_t(x);
        } else {
            w << byte(0xff);
            w << x;
        }
    }
    
    bytes read_bytes(reader r) {
        uint vi{read_var_int(r)};
        unsigned char len{static_cast<unsigned char>(vi)};
        if (vi > len) throw invalid_value{};
        std::vector<byte> v{};
        r >> v;
        return v;
    } */
    
} 

#endif
