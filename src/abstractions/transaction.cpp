// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/transaction.hpp>

namespace abstractions {
    
    static const string InvalidValueError = string{"Invalid value"};
    
    struct invalid_value : std::exception {
        const char* what() const noexcept final override {
            return InvalidValueError.c_str();
        }
    };
    
    struct reader : public data::slice_reader {
        using slice_reader::operator>>;
        reader(slice<byte> s) : slice_reader{s, boost::endian::order::little} {}
        reader(std::vector<byte>& v) : slice_reader{v, boost::endian::order::little} {}
        
        void operator>>(uint256& d) {
            for (byte& b : d) operator>>(b);
        }

    }; 
    
    struct writer : public data::slice_writer {
        using slice_writer::operator<<;
        writer(slice<byte> s) : slice_writer{s, boost::endian::order::little} {}
        writer(std::vector<byte>& v) : slice_writer{v, boost::endian::order::little} {}
        
        void operator<<(uint256& d) {
            for (byte b : d) operator<<(b);
        }
    }; 
    
    uint read_var_int(reader r) {
        byte b;
        r >> b;
        if (b < 0xfd) return b;
        
        if (b == 0xfd) {
            uint16_t x;
            r >> x;
            return x;
        }
        
        if (b == 0xfd) {
            uint32_t x;
            r >> x;
            return x;
        }
        
        uint x;
        r >> x;
        return x;
    }
        
    bytes read_bytes(reader r) {
        uint vi{read_var_int(r)};
        unsigned char len{static_cast<unsigned char>(vi)};
        if (vi > len) throw invalid_value{};
        std::vector<byte> v{};
        r >> v;
        return v;
    } 
    
    void write_var_int(writer w, uint x) {
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
        
    void write_bytes(writer w, bytes& b) {
        write_var_int(w, b.size());
        w << b;
    }
    
    template <typename txid> typename outpoint<txid>::representation read_outpoint(reader r) {
        typename outpoint<txid>::representation o{};
        r >> o.Reference;
        r >> o.Index;
        o.Valid = o.Reference.valid();
        return o;
    }
    
    template <typename txid> void write_outpoint(writer w, typename outpoint<txid>::representation o) {
        if (!o.valid()) throw invalid_value{};
        w << o.Reference;
        w << o.Index;
        return o;
    }
    
    template <typename txid> outpoint<txid>::representation::representation(const outpoint& o) noexcept {
        try {
           reader r{static_cast<std::vector<byte>&>(o)}; 
           *this = read_outpoint<txid>(r);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename txid> outpoint<txid>::outpoint(const representation&) noexcept {
        
    }
    
    template <typename txid>
    typename outpoint<txid>::representation&
    outpoint<txid>::representation::operator=(const representation& o) {
        Valid = o.Valid;
        Reference = o.Reference;
        Index = o.Index;
        return *this;
    }
    
    template <typename ops> typename output<ops>::representation read_output(reader r) {
        throw 0;
    }
    
    template <typename ops> output<ops>::representation::representation(const output& o) noexcept {
        throw 0;
    }
    
    template <typename ops> const slice<byte> output<ops>::script() const {
        throw 0;
    }
    
    template <typename ops> output<ops>::output(const representation&) noexcept {
        throw 0;
    }
    
    template <typename ops>
    typename output<ops>::representation&
    output<ops>::representation::operator=(const representation& o) {
        Valid = o.Valid;
        Value = o.Value;
        ScriptPubKey = o.ScriptPubKey;
        return *this;
    }
        
    template <typename txid, typename ops> input<txid, ops>::representation::representation(const input& i) noexcept {
        throw 0;
    }
        
    template <typename txid, typename ops> input<txid, ops>::input(const representation&) noexcept {
        throw 0;
    }
    
    template <typename txid, typename ops>
    typename input<txid, ops>::representation&
    input<txid, ops>::representation::operator=(const representation& i) {
        Valid = i.Valid;
        Outpoint = i.Outpoint;
        ScriptSignature = i.ScriptSignature;
        Sequence = i.Sequence;
        return *this;
    }
    
    template <typename in, typename out>
    transaction<in, out>::representation::representation(const transaction&) noexcept {
        throw 0;
    }
        
    template <typename in, typename out>
    transaction<in, out>::transaction(const representation&) noexcept {
        throw 0;
    }
    
    template <typename in, typename out>
    typename transaction<in, out>::representation&
    transaction<in, out>::representation::operator=(const representation& t) {
        Valid = t.Valid;
        Locktime = t.Locktime;
        Inputs = t.Inputs;
        Outputs = t.Outputs;
        return *this;
    }
    
} 
