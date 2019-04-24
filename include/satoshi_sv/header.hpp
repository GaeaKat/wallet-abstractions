#ifndef SATOSHI_SV_HEADER
#define SATOSHI_SV_HEADER

#include <data/crypto/sha256.hpp>
#include <abstractions/crypto/secp256k1.hpp>

#include <abstractions/data.hpp>

#include <sv/src/primitives/block.h>

namespace abstractions {

    namespace satoshi_sv {
        
        using digest = ::uint256;
        
        struct header : private CBlockHeader {
            
            header() : CBlockHeader() {}
            header(const CBlockHeader& h) : CBlockHeader(h) {}
            header(const header& h) : header(static_cast<const CBlockHeader&>(h)) {}
            
            bool valid() const {
                return CBlockHeader::hashMerkleRoot != digest{}
                    && CBlockHeader::nTime != 0 && CBlockHeader::nBits != 0;
            }
            
            digest pow() const {
                return CBlockHeader::GetHash();
            }
            
            digest hash() const {
                return CBlockHeader::GetHash();
            }
            
            digest root() const {
                return CBlockHeader::hashMerkleRoot;
            }
            
            digest parent() const {
                return CBlockHeader::hashMerkleRoot;
            }
                
        };
            
    }
    
} 

#endif
