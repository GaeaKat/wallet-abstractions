#ifndef ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP

#include <abstractions/blockchain/merkle.hpp>

namespace abstractions 
{
        
    template <typename point, typename tx, typename digest, typename header>
    struct blockchain {
        struct transaction {
            tx Transaction;
            N Index;
            digest Block;
        };
        
        virtual transaction operator[](point) const = 0;
        
        virtual header get_header(digest header_digest) const = 0; 
        
        virtual merkle::partial<digest> get_merkle_tree(digest root) const = 0;
    };
    
} 

#endif
