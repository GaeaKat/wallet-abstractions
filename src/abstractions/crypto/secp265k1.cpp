// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/crypto/address.hpp>
#include <data/encoding/base58.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::secp256k1 {
    
    namespace wif {
        namespace compressed {
            const size_t wif_compressed_size{38};
            typedef std::array<byte, wif_compressed_size> wif_compressed;

            bool read(string& s, secret& p) {
                data::encoding::base58::string b58{s};
                if (!b58.valid()) return false;
                bytes b = b58;
                if (b.size() != wif_compressed_size) return false;
                if (!crypto::verify_checksum(b)) return false;
                if (b[0] != 0x80 || b[33] != 0x01) return false;
                std::copy(b.begin() + 1, b.end() - 5, p.Value.begin());
                if (!p.valid()) return false;
                throw data::method::unimplemented{};
            }
            
            string write(const secret& s) {
                std::vector<byte> wif{wif_compressed_size};
                wif[0] = 0x80;
                wif[33] = 0x01;
                std::copy(s.Value.begin(), s.Value.end(), wif.begin() + 1);
                std::array<byte, 4> checksum = crypto::checksum(slice<byte>{wif}.range(0, 34));
                std::copy(checksum.begin(), checksum.end(), wif.begin() + 34);
                return data::encoding::base58::write(wif);
            }
            
            bool read(string& s, compressed_pubkey& p) {
                data::encoding::hex::string hex{s};
                if (!hex.valid()) return false;
                bytes b = hex;
                if (b.size() != data::crypto::secp256k1::compressed_pubkey_size) return false;
                std::copy_n(b.begin(), data::crypto::secp256k1::compressed_pubkey_size, p.begin());
                return true;
            }
            
            string write(const compressed_pubkey& p) {
                return data::encoding::hex::write(static_cast<const std::array<byte, data::crypto::secp256k1::compressed_pubkey_size>>(p));
            }
        }
        
        namespace uncompressed {
            const size_t wif_uncompressed_size{37};
            typedef std::array<byte, wif_uncompressed_size> wif_uncompressed;

            bool read(string& s, secret& p) {
                data::encoding::base58::string b58{s};
                if (!b58.valid()) return false;
                bytes b = b58;
                if (b.size() != wif_uncompressed_size) return false;
                if (!crypto::verify_checksum(b)) return false;
                if (b[0] != 0x80) return false;
                std::copy(b.begin() + 1, b.end() - 4, p.Value.begin());
                if (!p.valid()) return false;
            }
            
            string write(const secret& s) {
                std::vector<byte> wif{wif_uncompressed_size};
                wif[0] = 0x80;
                std::copy(s.Value.begin(), s.Value.end(), wif.begin() + 1);
                std::array<byte, 4> checksum = crypto::checksum(slice<byte>{wif}.range(0, 34));
                std::copy(checksum.begin(), checksum.end(), wif.begin() + 34);
                return data::encoding::base58::write(wif);
            }
            
            bool read(string& s, uncompressed_pubkey& p) {
                data::encoding::hex::string hex{s};
                if (!hex.valid()) return false;
                bytes b = hex;
                if (b.size() != data::crypto::secp256k1::uncompressed_pubkey_size) return false;
                std::copy_n(b.begin(), data::crypto::secp256k1::uncompressed_pubkey_size, p.begin());
                return true;
            }
            
            string write(const uncompressed_pubkey& p) {
                return data::encoding::hex::write(static_cast<const std::array<byte, data::crypto::secp256k1::uncompressed_pubkey_size>>(p));
            }
        }
    }
    
} 

