// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <bitcoin/system/wallet/payment_address.hpp>
#include <abc/src/cashaddr.h>
#include <abstractions/crypto/address.hpp>


namespace abstractions::bitcoin {

    address::address(const pubkey &p) : address{p.address()} {};

    address::address(const secret &s) : address{s.address()} {};

    namespace bitcoin_address {
        address read(const string &base58) {
            libbitcoin::system::wallet::payment_address addr{base58};
            if (!addr) return {};
            libbitcoin::system::short_hash tmp{};
            return {address::digest{data::uint<data::ripemd160::size>{addr.hash()}}};
        }

        data::string write(const address &a) {
            return libbitcoin::system::wallet::payment_address{(const std::array<byte, 20> &) (a)}.encoded();
        }
    }

    namespace cashaddr {
        string prefix = "bitcoincash";

        address read(const string &s) {
            auto p = abc::cashaddr::Decode(s, prefix);
            if (p.first == "") return {};
            data::uint<data::ripemd160::size> addr;
            std::copy_n(p.second.begin(), data::ripemd160::size, addr.begin());
            return {address::digest{data::uint<data::ripemd160::size>{addr}}};
        }

        data::string write(const address& a) {
            std::vector<byte> v{20};
            std::copy(a.Digest.Digest.begin(), a.Digest.Digest.end(), v.begin());
            return abc::cashaddr::Encode(prefix, v);
        }

    }
}
namespace abstractions {
    bool crypto::verify_checksum(const slice<byte> &wif) {
        slice<byte> checksum = wif.range(-4);
        slice<byte> toCheck = wif.range(0, -4);
        data::sha256::digest stage1Checksum = data::sha256::hash(toCheck);
        data::sha256::digest stage2Checksum = data::sha256::hash(stage1Checksum.Digest);
        slice<byte> checkChecksum = slice<byte>::make(stage2Checksum.Digest.Array).range(0, 4);
        return checksum == checkChecksum;
    }

    std::array<byte, 4> crypto::checksum(const slice<byte> &data) {
        slice<byte> toCheck = data;
        data::sha256::digest stage1Checksum = data::sha256::hash(toCheck);
        data::sha256::digest stage2Checksum = data::sha256::hash(stage1Checksum.Digest);
        std::array<byte, 4> tmp{};
        std::copy_n(stage2Checksum.Digest.begin(), 4, tmp.begin());
        return tmp;

    }
}