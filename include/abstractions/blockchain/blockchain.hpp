#ifndef ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP

#include <abstractions/blockchain/merkle.hpp>
#include <abstractions/blockchain/header.hpp>

namespace abstractions 
{
        
    template <typename point, typename tx, typename digest, typename hdr>
    struct blockchain {
        struct output {
            tx Transaction;
            digest Block;
            
        private:
            output(tx t, digest b) : Transaction{t}, Block{b} {}
        };
        
        virtual const output operator[](point) const = 0;
        
        virtual block::header<digest, hdr> header(digest) const = 0; 
        
        virtual merkle::partial<digest> merkle(digest root) const = 0;
    };
    
} 

#endif
