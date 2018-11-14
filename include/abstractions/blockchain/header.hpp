#ifndef ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP

#include <abstractions/list.hpp>
#include <abstractions/blockchain/merkle.hpp>

namespace abstractions 
{
    
    namespace block
    {
        
        template <typename hdr, typename N, typename pow>
        N cumulative_pow(pow p, list<hdr> lh) {
            struct pv {
                N Value;
                
                pv(hdr h) : Value{p(h)} {}
                pv(N v) : Value(v) {}
                
                pv operator+(pv pp) const {
                    return pv{Value + pp.Value};
                }
            };
            
            return reduce(lh, pv{0}).Value;
        }
        
        template <typename tx, typename block, typename hash, typename root, typename digest>
        inline bool contains(tx t, block b, merkle::derivation<digest> d, hash h, root r) {
            return merkle::check(merkle::root_to_leaf<digest>{r(b), h(t)}, d);
        }
        
        template <typename I, typename P>
        inline bool check(I i, P p) {
            return contains(i.Transaction, i.Block, p.Merkle, p.Hash, p.Root);
        }
        
        // A statement that a transaction exists in a block. 
        template <typename tx, typename block>
        struct in {
            tx Transaction;
            block Block;
            
            in(tx t, block b) : Transaction{t}, Block{b} {}
        };
        
        template <typename digest, typename hash, typename root>
        struct derivation {
            merkle::derivation<digest> Merkle;
            hash Hash;
            root Root;
        };
        
        template <typename proposition, typename derivation>
        proof<bool (*)(proposition, derivation), proposition, derivation> state_proof(proposition p, derivation d) {
            return proof<bool (*)(proposition, derivation), proposition, derivation>{check<proposition, derivation>, p, d};
        }

    }
    
} 

#endif
