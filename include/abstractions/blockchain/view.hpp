#ifndef ABSTRACTIONS_BLOCKCHAIN_VIEW_HPP
#define ABSTRACTIONS_BLOCKCHAIN_VIEW_HPP

#include <abstractions/chain.hpp>
#include <abstractions/blockchain/blockchain.hpp>
#include <abstractions/blockchain/header.hpp>

namespace abstractions 
{
        
    template <typename point, typename tx, typename digest, typename hdr, typename hash, typename parent, typename root>
    class view : public blockchain<point, tx, digest, hdr> {
        using output = typename blockchain<point, tx&, digest, hdr>::output;
        
        block::chain<digest, hdr, hash, parent> Chain;
        
        // The partial merkle trees, indexed my Merkle root.
        map<digest, merkle::partial<digest>> Merkle;
        
        // The function that gets the merkle root from a header. 
        root Root;
        
        // All transactions contained in this view. 
        list<tx> Transactions;
        
        map<digest, tx*> tx_by_hash;
        
        // All transactions that we know what block it's in. 
        map<tx*, digest> Blocks;
        
        map<point, tx&> Outpoints;
        
    public:
        virtual output operator[](point p) const override {
            tx& t = Outpoints[p];
            return output{t, Blocks[&t]};
        };
        
        virtual hdr header(digest d) const override {
            return Chain.header(d);
        }; 
        
        virtual merkle::partial<digest> merkle(digest root) const override {};
    };
    
} 

#endif
