// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_HEADER
#define SATOSHI_SV_HEADER

#include <data/crypto/secp256k1.hpp>

#include <abstractions/abstractions.hpp>
#include <abstractions/timechain/header.hpp>

#include <satoshi_sv/sv.hpp>

#include <satoshi_sv/src/primitives/block.h>

namespace abstractions::sv {
    
    struct header : private CBlockHeader {
        using CBlockHeader::CBlockHeader;
        
        header() : CBlockHeader() {}
        header(const CBlockHeader& h) : CBlockHeader(h) {}
        header(const header& h) : header(static_cast<const CBlockHeader&>(h)) {}
        
        bool valid() const {
            return CBlockHeader::hashMerkleRoot != digest{}
                && CBlockHeader::nTime != 0 && CBlockHeader::nBits != 0;
        }  
        
        sha256::digest pow() const {
            return convert(CBlockHeader::GetHash());
        }
        
        sha256::digest hash() const {
            return convert(CBlockHeader::GetHash());
        }
        
        sha256::digest root() const {
            return convert(CBlockHeader::hashMerkleRoot);
        }
        
        sha256::digest parent() const {
            return convert(CBlockHeader::hashMerkleRoot);
        }
        
        
        constexpr static timechain::header::interface<header, sha256::digest> is_header{};
    };
    
} 

#endif
