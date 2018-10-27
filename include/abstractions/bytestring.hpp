#ifndef ABSTRACTIONS_BYTESTRING_HPP
#define ABSTRACTIONS_BYTESTRING_HPP

#include <abstractions/slice.hpp>
#include <abstractions/endian.hpp>

namespace abstractions {
    
    using bytestring = slice<byte>;
    
    class reader {
        bytestring::iterator i;
        bytestring::iterator e;
        
    public: 
        bool Valid;
        
    private:
        reader(bytestring b) : i(b.begin()), e(b.end()), Valid(true) {}
        reader(bytestring::iterator ee) : i(ee), e(ee), Valid(false) {}

    public:
        static reader make(bytestring b) {
            return reader(b);
        }
        
        reader read(byte&) const;
        
        reader read(bytestring&) const;
        
        reader read(uint16_t&) const;
        
        reader read(uint32_t&) const;
        
        reader read(endian::ness, uint16_t&) const;
        
        reader read(endian::ness, uint32_t&) const;
        
        reader read(endian::ness, uint64_t&) const;
    };
    
    class writer {
        bytestring::iterator i;
        bytestring::iterator e;
        
    public: 
        bool Valid;
        
        writer& operator=(writer w) {
            i = w.i;
            e = w.e;
            return *this;
        }
        
    private:
        writer(bytestring::iterator initial, bytestring::iterator end) : i(initial), e(end), Valid(true) {}
        writer(bytestring::iterator ee) : i(ee), e(ee), Valid(false) {}

    public:
        static writer make(bytestring& b) {
            return writer(b.begin(), b.end());
        }
        
        writer write(const byte) const;
        
        writer write(const bytestring) const;
        
        writer write(uint16_t) const;
        
        writer write(uint32_t) const;
        
        writer write(endian::ness, uint16_t) const;
        
        writer write(endian::ness, uint32_t) const;
        
        writer write(endian::ness, uint64_t) const;
    };

}

#endif 
