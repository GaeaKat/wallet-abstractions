// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_TIMECHAIN_TIMECHAIN
#define ABSTRACTIONS_TIMECHAIN_TIMECHAIN

#include <abstractions/abstractions.hpp>
#include <data/slice.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::timechain {
    
    using digest = data::endian::ordered<data::slice<byte, 32>, data::endian::order::little>;
    
    using uint32 = data::endian::ordered<uint32, data::endian::order::little>;
    
    using int32 = data::endian::ordered<int32, data::endian::order::little>;
    
    using satoshi = data::endian::ordered<uint64, data::endian::order::little>;
    
    static const string InvalidValueError = string{"Invalid value"};
    
    struct invalid_value : std::exception {
        const char* what() const noexcept final override {
            return InvalidValueError.c_str();
        }
    };
    
    struct reader {
        data::reader Reader;
        reader(bytes b) : Reader{data::slice<byte>::make(b)} {}
        
        reader operator>>(uint32&) const {
            throw data::method::unimplemented{};
        }
        
        reader operator>>(int32&) const {
            throw data::method::unimplemented{};
        }
        
        reader operator>>(satoshi&) const {
            throw data::method::unimplemented{};
        }
        
        reader operator>>(digest&) const {
            throw data::method::unimplemented{};
        }
        
        reader operator>>(bytes&) const {
            throw data::method::unimplemented{};
        }
        
        reader read_var_int(uint&) const {
            throw data::method::unimplemented{};
        }
    }; 
    
    struct writer {
        data::writer Writer;
        writer(bytes b) : Writer{data::slice<byte>::make(b)} {}
        
        writer operator<<(uint32) const {
            throw data::method::unimplemented{};
        }
        
        writer operator<<(int32) const {
            throw data::method::unimplemented{};
        }
        
        writer operator<<(satoshi) const {
            throw data::method::unimplemented{};
        }
        
        writer operator<<(digest) const {
            throw data::method::unimplemented{};
        }
        
        writer operator<<(bytes) const {
            throw data::method::unimplemented{};
        }
        
        writer write_var_int(uint) const {
            throw data::method::unimplemented{};
        }
    }; 
    
    inline size_t var_int_size(uint) {
        throw data::method::unimplemented{};
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
