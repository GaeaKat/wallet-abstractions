// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/script/script.hpp>

namespace abstractions::script {
    
    struct writer {
        timechain::writer Writer;
        writer operator<<(instruction o) const {
            return writer{write(Writer, o)};
        }
        
        writer operator<<(program p) const {
            return writer{write(Writer, p)};
        }
        
        writer(timechain::writer w) : Writer{w.Writer} {}
        writer(bytes& b) : Writer{timechain::writer{data::slice<byte>{b}}} {}
    };
    
    timechain::reader read_push(timechain::reader r, instruction& rest) {
        uint32 size;
        if (rest.Op <= OP_PUSHSIZE75) size = rest.Op;
        if (rest.Op == OP_PUSHDATA1) {
            byte x;
            r = r >> x;
            size = x;
        }
        if (rest.Op == OP_PUSHDATA2) {
            uint16_little x;
            r = r >> x;
            size = x;
        }
        if (rest.Op == OP_PUSHDATA4) {
            uint32_little x;
            r = r >> x;
            size = x;
        }
        rest.Data.resize(size);
        return r >> rest.Data;
    }
    
    struct reader {
        timechain::reader Reader;
        reader operator>>(instruction& i) const {
            byte next;
            timechain::reader r = Reader >> next;
            i.Op = op{next};
            if (is_push_data(i.Op)) return read_push(r, i);
            return r;
        }
        
        bool empty() const {
            return Reader.empty();
        }
        
        reader(timechain::reader r) : Reader{r} {}
        reader(bytes_view b) : Reader{timechain::reader{b}} {}
    };
    
    // TODO there is an exception thrown here. 
    // I am not initializing the string correctly. 
    // I don't know how to do it right. 
    bytes compile(program p) {
        bytes compiled{};
        compiled.resize(length(p));
        writer{compiled} << p;
        return compiled;
    }
    
    program decompile(bytes_view b) {
        program p{};
        reader r{b};
        while(!r.empty()) {
            instruction i{};
            r = r >> i;
            p = p + i;
        }
        return p;
    }
    
}

std::ostream& operator<<(std::ostream& o, abstractions::script::op x) {
    if (x == abstractions::script::OP_FALSE) return o << "push_empty";
    if (is_push(x)) {
        switch(x) {
            case abstractions::script::OP_PUSHDATA1 : return o << "push_data_1";
            case abstractions::script::OP_PUSHDATA2 : return o << "push_data_2";
            case abstractions::script::OP_PUSHDATA4 : return o << "push_data_4";
            default : return o << "push_size_" << int{x};
        }
    }
    
    switch (x) {
        default : return o << "***unknown op code***";
        case abstractions::script::OP_CHECKSIG: return o << "checksig";
        case abstractions::script::OP_CHECKSIGVERIFY: return o << "checksig_verify";
        case abstractions::script::OP_EQUALVERIFY: return o << "equal_verify";
        
        case abstractions::script::OP_1NEGATE: return o << "push_-1";
        
        case abstractions::script::OP_RESERVED: return o << "reserved";
        
        case abstractions::script::OP_1: return o << "push_true";
        case abstractions::script::OP_2: return o << "push_2";
        case abstractions::script::OP_3: return o << "push_3";
        case abstractions::script::OP_4: return o << "push_4";
        case abstractions::script::OP_5: return o << "push_5";
        case abstractions::script::OP_6: return o << "push_6";
        case abstractions::script::OP_7: return o << "push_7";
        case abstractions::script::OP_8: return o << "push_8";
        case abstractions::script::OP_9: return o << "push_9";
        case abstractions::script::OP_10: return o << "push_10";
        case abstractions::script::OP_11: return o << "push_11";
        case abstractions::script::OP_12: return o << "push_12";
        case abstractions::script::OP_13: return o << "push_13";
        case abstractions::script::OP_14: return o << "push_14";
        case abstractions::script::OP_15: return o << "push_15";
        case abstractions::script::OP_16: return o << "push_16";
        
        case abstractions::script::OP_NOP: return o << "nop";
        case abstractions::script::OP_VER: return o << "ver";
        case abstractions::script::OP_IF: return o << "if";
        case abstractions::script::OP_NOTIF: return o << "not_if";
        case abstractions::script::OP_VERIF: return o << "ver_if";
        case abstractions::script::OP_VERNOTIF: return o << "ver_not_if";
        case abstractions::script::OP_ELSE: return o << "else";
        case abstractions::script::OP_ENDIF: return o << "end_if";
        case abstractions::script::OP_VERIFY: return o << "verify";
        case abstractions::script::OP_RETURN: return o << "return";

        case abstractions::script::OP_TOALTSTACK: return o << "to_alt_stack";
        case abstractions::script::OP_FROMALTSTACK: return o << "from_alt_stack";
        case abstractions::script::OP_2DROP: return o << "2_drop";
        case abstractions::script::OP_2DUP: return o << "2_dup";
        case abstractions::script::OP_3DUP: return o << "3_dup";
        case abstractions::script::OP_2OVER: return o << "2_over";
        case abstractions::script::OP_2ROT: return o << "2_rot";
        case abstractions::script::OP_2SWAP: return o << "2_swap";
        case abstractions::script::OP_IFDUP: return o << "if_dup";
        case abstractions::script::OP_DEPTH: return o << "depth";
        case abstractions::script::OP_DROP: return o << "drop";
        case abstractions::script::OP_DUP: return o << "dup";
        case abstractions::script::OP_NIP: return o << "nip";
        case abstractions::script::OP_OVER: return o << "over";
        case abstractions::script::OP_PICK: return o << "pick";
        case abstractions::script::OP_ROLL: return o << "roll";
        case abstractions::script::OP_ROT: return o << "rot";
        case abstractions::script::OP_SWAP: return o << "swap";
        case abstractions::script::OP_TUCK: return o << "tuck";
        
    }
}
