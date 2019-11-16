// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/work/work.hpp>
#include <abstractions/timechain/timechain.hpp>

namespace abstractions::work {
    
    // roughly 1/16 odds. 
    const target minimum{32, 0x000fffff};
    
    message bitcoin_header(sha256::digest d, uint32 timestamp) {
        message m{};
        std::copy(d.Digest.begin(), d.Digest.end(), m.begin());
        m.words().set(8, timestamp);
        return m;
    };
    
    message public_key(bitcoin::pubkey d) {
        message m{};
        m.words().set(0, 0);
        std::copy(d.Pubkey.begin(), d.Pubkey.end(), m.begin() + 3);
        return m;
    };
    
    message reference_and_pubkey(sha256::digest d, bitcoin::pubkey p, uint24 sequence) {
        throw data::method::unimplemented{"work::reference_and_pubkey, work.cpp line 13"};
    }
    
    data::uint<80> candidate::write(int64 i, order o) {
        data::uint<80> data;
        bytes_view message{o.Message.Array.data(), o.Message.Array.size()};
        timechain::writer{data::slice<byte>::make(data)} << int32(data::greater(i)) << message << uint32_little{o.Target} << data::lesser(i);
        return data;
    }
    
    int64 work(order o) {
        if (o.Target < minimum) throw std::invalid_argument{"minimum target"};
        int64 nonce = 0;
        while (true) {
            if (candidate{nonce, o}.valid()) return nonce;
            nonce++;
        }
    }
    
}
