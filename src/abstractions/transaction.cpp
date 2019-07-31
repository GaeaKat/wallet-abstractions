// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/transaction.hpp>
#include <data/encoding/words.hpp>

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
            for (uint32& x : d.words()) operator>>(x);
        }

    }; 
    
    struct writer : public data::slice_writer {
        using slice_writer::operator<<;
        writer(slice<byte> s) : slice_writer{s, boost::endian::order::little} {}
        writer(std::vector<byte>& v) : slice_writer{v, boost::endian::order::little} {}
        
        void operator<<(uint256& d) {
            for (uint32 x : d.words()) operator<<(x);
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
        
        if (b == 0xfe) {
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
    
    template <typename ops>
    void write_script(writer w, ops b);
    
    template <typename ops>
    void read_script(reader r, ops);
    
    template <typename txid> void read_outpoint(reader r, typename outpoint<txid>::representation& o) {
        r >> o.Reference;
        r >> o.Index;
        o.Valid = o.Reference.valid();
    }
    
    template <typename txid> void write_outpoint(writer w, typename outpoint<txid>::representation& o) {
        if (!o.valid()) throw invalid_value{};
        w << o.Reference;
        w << o.Index;
    }
    
    template <typename ops> void read_output(reader r, typename output<ops>::representation& o) {
        r >> o.Value;
        read_script<ops>(r, o.ScriptPubKey);
        o.Valid = o.ScriptPubKey.valid();
    }
    
    template <typename ops> void write_output(writer w, typename output<ops>::representation& o) {
        if (!o.valid()) throw invalid_value{};
        w << o.Value;
        write_script(w, o.ScriptPubKey);
    }
    
    template <typename txid, typename ops> void read_input(reader r, typename input<txid, ops>::representation& i) {
        read_outpoint(r, i.Outpoint);
        i.ScriptSignature = read_script<ops>(r);
    }
    
    template <typename txid, typename ops> void write_input(writer w, typename input<txid, ops>::representation i) {
        if (!i.valid()) throw invalid_value{};
        write_outpoint(w, i.Outpoint);
        write_script(w, i.ScriptPubKey);
    }
    
    template <typename in, typename out> void read_transaction(reader r, typename transaction<in, out>::representation& t) {
        r >> t.Version;
        uint num_inputs = read_var_int(r);
        vector<in> inputs{num_inputs};
        for (in& i : inputs) read_input(r, i);
        t.Inputs = inputs;
        uint num_outputs = read_var_int(r);
        vector<out> outputs{num_outputs};
        for (out& o : outputs) read_input(r, o);
        t.Outputs = outputs;
        r >> t.Locktime;
    }
    
    template <typename in, typename out> void write_transaction(writer w, typename transaction<in, out>::representation t) {
        if (!t.valid()) throw invalid_value{};
        w << t.Version;
        write_var_int(w, t.Inputs.size());
        for (in& i : t.Inputs) write_input(w, i);
        write_var_int(w, t.Outputs.size());
        for (out& o : t.Outputs) write_input(w, o);
        w << t.Locktime;
    }
    
    uint var_int_size(uint x) {
        if (x < 0xfd) return 1;
        if (x <= 0xffff) return 3;
        if (x <= 0xffffffff) return 5;
        return 9;
    }
    
    const uint outpoint_size = 36;
    
    template <typename txid>
    uint serialized_size(const typename outpoint<txid>::representation&) {
        return outpoint_size;
    }
    
    template <typename ops>
    uint serialized_size(const typename output<ops>::representation& o) {
        uint script_size = o.ScriptPubKey.size();
        return 8 + var_int_size(script_size) + script_size;
    }
    
    template <typename txid, typename ops>
    uint serialized_size(const typename input<txid, ops>::representation& i) {
        uint script_size = i.ScriptSignature.size();
        return outpoint_size + 4 + var_int_size(script_size) + script_size;
    }
    
    template <typename in, typename out>
    uint serialized_size(const typename transaction<in, out>::representation& t) {
        uint size = 8 + var_int_size(t.Inputs.size()) + var_int_size(t.Outputs.size());
        for (in& i : t.Inputs) size += serialized_size(i);
        for (out& o : t.Outputs) size += serialized_size(o);
        return size;
    }
    
    template <typename txid> outpoint<txid>::representation::representation(const outpoint& o) noexcept {
        try {
           reader r{static_cast<std::vector<byte>&>(o)}; 
           read_outpoint<txid>(r, *this);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename txid> outpoint<txid>::outpoint(const representation& o) noexcept : std::vector<byte>{serialized_size(o)} {
        try {
            writer w{static_cast<std::vector<byte>&>(o)};
            write_outpoint(w, *this);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename ops> output<ops>::representation::representation(const output& o) noexcept {
        try {
           reader r{static_cast<std::vector<byte>&>(o)}; 
           read_output(r, *this);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename ops> output<ops>::output(const representation& o) noexcept : std::vector<byte>{serialized_size(o)} {
        try {
            writer w{static_cast<std::vector<byte>&>(o)};
            write_output(w, *this);
        } catch (...) {
            *this = {};
        }
    }
        
    template <typename txid, typename ops> input<txid, ops>::representation::representation(const input& i) noexcept {
        try {
           reader r{static_cast<std::vector<byte>&>(i)}; 
           read_input(r, *this);
        } catch (...) {
            *this = {};
        }
    }
        
    template <typename txid, typename ops> input<txid, ops>::input(const representation& i) noexcept : std::vector<byte>{serialized_size(i)} {
        try {
            writer w{static_cast<std::vector<byte>&>(i)};
            write_input(w, *this);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename in, typename out>
    transaction<in, out>::representation::representation(const transaction& t) noexcept {
        try {
           reader r{static_cast<std::vector<byte>&>(t)}; 
           read_transaction<in, out>(r, *this);
        } catch (...) {
            *this = {};
        }
    }
        
    template <typename in, typename out>
    transaction<in, out>::transaction(const representation& t) noexcept : std::vector<byte>{serialized_size(t)} {
        try {
            writer w{static_cast<std::vector<byte>&>(t)};
            write_transaction(w, *this);
        } catch (...) {
            *this = {};
        }
    }
    
    template <typename txid>
    typename outpoint<txid>::representation&
    outpoint<txid>::representation::operator=(const representation& o) {
        Valid = o.Valid;
        Reference = o.Reference;
        Index = o.Index;
        return *this;
    }
    
    template <typename ops>
    typename output<ops>::representation&
    output<ops>::representation::operator=(const representation& o) {
        Valid = o.Valid;
        Value = o.Value;
        ScriptPubKey = o.ScriptPubKey;
        return *this;
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
    typename transaction<in, out>::representation&
    transaction<in, out>::representation::operator=(const representation& t) {
        Valid = t.Valid;
        Version = t.Version;
        Inputs = t.Inputs;
        Outputs = t.Outputs;
        Locktime = t.Locktime;
        return *this;
    }
    
} 
