#include <abstractions/crypto/address.hpp>

namespace abstractions {
    std::array<byte, 4> crypto::checksum(bytes_view data) {
        data::sha256::digest check = hash256(data);
        std::array<byte, 4> tmp{};
        std::copy_n(check.Digest.begin(), 4, tmp.begin());
        return tmp;
    }
    
    bool crypto::verify_checksum(bytes_view wif) {
        auto check = checksum(wif.substr(0, wif.size() - 4));
        return wif.substr(wif.size() - 4) == bytes_view{check.data(), check.size()};
    }
}
