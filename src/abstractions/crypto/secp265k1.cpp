// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/crypto/secp256k1.hpp>
#include <abstractions/crypto/address.hpp>
#include <abstractions/transaction.hpp>
#include <data/encoding/base58.hpp>
#include <satoshi_sv/sv.hpp>
#include <key.h>
#include <script/sighashtype.h>
#include <iostream>

namespace abstractions::secp256k1 {
    
    signature sign(const bytes_view out, const bytes_view tx, uint32 index, secret key) {
        timechain::output::serialized o{out};
        CTransaction ct = sv::read_transaction(tx); 
        std::vector<byte> vchSig;
        
        CKey k{};
        k.Set(key.Value.begin(), key.Value.end(), 
            true // TODO I don't think this should matter though. 
        );
        bytes_view script = o.script();
        CScript cs = sv::read_script(script);
        SigHashType x{};
        ::uint256 hash = SignatureHash(cs, ct, index, x, Amount{(uint64)(o.value())});
        if (!k.Sign(hash, vchSig)) {
            return {};
        }

        vchSig.push_back(uint8_t(x.getRawSigHashType()));
        
        return signature{vchSig.begin(), vchSig.end()};
    }
    
    namespace wif {
        namespace compressed {
            // why is wif compressed bigger than wif uncompressed? 
            // because compressed keys were invented after uncompressed keys. 
            // A compressed wif code is denoted with an extra character to
            // distinguish it from an uncompressed wif code. 
            const size_t wif_compressed_size=38;
            typedef std::array<byte, wif_compressed_size> wif_compressed;

            bool read(string& s, secret& p) {
                try {
                    data::encoding::base58::string b58{s};
                    if (!b58.valid()) return false;
                    bytes b = static_cast<bytes>(b58);
                    if (b.size() != wif_compressed_size) return false;
                    if (!crypto::verify_checksum(b)) return false;
                    if (b[0] != 0x80 || b[33] != 0x01) return false;
                    std::copy(b.begin() + 1, b.end() - 5, p.Value.begin());
                    return p.valid();
                }
                catch(...)
                {
                    return false;
                }
            }
            
            string write(const secret& s) {
                bytes wif{};
                wif.resize(wif_compressed_size);
                wif[0] = 0x80;
                wif[33] = 0x01;
                std::copy(s.Value.begin(), s.Value.end(), wif.begin() + 1);
                std::array<byte, 4> checksum = crypto::checksum(wif.substr(0, 34));
                std::copy(checksum.begin(), checksum.end(), wif.begin() + 34);
                return data::encoding::base58::write(wif);
            }
            
            bool read(string& s, compressed_pubkey& p) {
                try {
                    data::encoding::hex::string hex{s};
                    if (!hex.valid()) return false;
                    if (bytes(hex).size() != data::crypto::secp256k1::compressed_pubkey_size) return false;
                    std::copy_n(bytes(hex).begin(), data::crypto::secp256k1::compressed_pubkey_size, p.Value.begin());
                    return true;
                }
                catch(...)
                {
                    return false;
                }
            }
            
            string write(const compressed_pubkey& p) {
                return data::encoding::hex::write(p);
            }
        }
        
        namespace uncompressed {
            const size_t wif_uncompressed_size{37};
            typedef std::array<byte, wif_uncompressed_size> wif_uncompressed;

            bool read(string& s, secret& p) {
                try {
                    data::encoding::base58::string b58{s};
                    if (!b58.valid()) return false;
                    bytes b = static_cast<bytes>(b58);
                    if (b.size() != wif_uncompressed_size) return false;
                    if (!crypto::verify_checksum(b)) return false;
                    if (b[0] != 0x80) return false;
                    std::copy(b.begin() + 1, b.end() - 4, p.Value.begin());
                    return p.valid();
                }
                catch(...)
                {
                    return false;
                }
            }
            
            string write(const secret& s) {
                bytes wif{};
                wif.resize(wif_uncompressed_size);
                wif[0] = 0x80;
                std::copy(s.Value.begin(), s.Value.end(), wif.begin() + 1);
                std::array<byte, 4> checksum = crypto::checksum(wif.substr(0, 33));
                std::copy(checksum.begin(), checksum.end(), wif.begin() + 33);
                return data::encoding::base58::write(wif);
            }
            
            bool read(string& s, uncompressed_pubkey& p) {
                try {
                    data::encoding::hex::string hex{s};
                    if (!hex.valid()) return false;
                    if (bytes(hex).size() != data::crypto::secp256k1::uncompressed_pubkey_size) return false;
                    std::copy_n(bytes(hex).begin(), data::crypto::secp256k1::uncompressed_pubkey_size, p.Value.begin());
                    return true;
                }
                catch(...)
                {
                    return false;
                }
            }
            
            string write(const uncompressed_pubkey& p) {
                return data::encoding::hex::write(p);
            }
        }
    }
    
} 

