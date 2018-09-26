#ifndef ABSTRACTIONS_SPV_VIEW_HPP
#define ABSTRACTIONS_SPV_VIEW_HPP

#include "tree.hpp"
#include <abstractions/blockchain/merkle.hpp>
#include <abstractions/blockchain/transaction.hpp>
#include <abstractions/blockchain/outpoint.hpp>
#include <abstractions/wallet.hpp>

namespace abstractions  {
    
    namespace block {
        
        template <typename digest, typename out, typename tx, typename hdr>
        wallet<outpoint<digest>, out> view(
            transaction::outpoints<tx, outpoint<digest>> ins,
            transaction::outputs<tx, out> outs, 
            list<hdr> ch,
            map<digest, merkle::partial_tree<digest>> mrk, 
            map<digest, tx> txs) {
            // should really use a std::map and convert.
            wallet<outpoint<digest>, out> w{};
            
            // Run down the headers in t.
            for (hdr h : ch) {
                for (digest tx_hash : mrk[root(h)].Transactions) {
                    tx x = txs[tx_hash];
                    if (x != tx{}) {
                        for (outpoint<digest> o : ins(x)) w = w.remove(o);
                        for (out o : outs(x)) for 
                    }
                }
            }
            
            return w;
        }
    
    }
    
} 

#endif
