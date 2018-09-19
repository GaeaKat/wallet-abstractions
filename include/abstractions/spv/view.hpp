#ifndef ABSTRACTIONS_SPV_VIEW_HPP
#define ABSTRACTIONS_SPV_VIEW_HPP

#include "tree.hpp"
#include <abstractions/blockchain/merkle.hpp>
#include <abstractions/blockchain/transaction.hpp>
#include <abstractions/blockchain/outpoint.hpp>
#include <abstractions/invalid.hpp>

namespace abstractions  {
    
    namespace block {
        
        template <typename point, typename out>
        using chain = map<point, out>;
        
        template <typename digest, typename out, typename tx, typename header>
        chain<outpoint<digest>, out> view(
            transaction::outpoints<tx, outpoint<digest>> ins,
            transaction::outputs<tx, out> outs, 
            tree<digest, header> t, 
            merkle::proofs<digest> p, 
            map<digest, tx> txs, 
            digest viewpoint) {
            // could do a non-functional map here and convert it. 
            map<outpoint<digest>, out> m;
            
            // Run down the headers in t.
            for (header h = t.Headers[viewpoint]; h != invalid<header>; h = t.Headers[t.Parent(h)]) {
                digest r = root(h);
                
                // go through all the proofs for each header. 
                for (list<typename merkle::proofs<digest>::entry> le = p[r]; le != nullptr; le = le->Next) 
                    // we should be able to expect that txs[le->First] exists because
                    // otherwise why would we have a merkle proof about it?
                    for (outpoint<digest> pt : ins(txs[le->First])) {
                        tx x = txs[pt.Digest];
                        
                        // outs(x)[pt.Index] would not exist if there wasn't a merkle proof. 
                        if (x != invalid<tx>) m = m.insert(pt, outs(x)[pt.Index]);
                    }
            }
            
            return m;
        }
    
    }
    
} 

#endif
