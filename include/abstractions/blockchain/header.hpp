#ifndef ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP

#include <abstractions/list.hpp>
#include <abstractions/blockchain/merkle.hpp>
#include <abstractions/optional.hpp>

namespace abstractions 
{
    
    namespace header
    {
        
        template <typename digest>
        const digest Genesis;
        
        template <typename hdr, typename N>
        N pow(hdr);
        
        template <typename hdr, typename digest>
        digest hash(hdr);
        
        template <typename hdr, typename digest>
        digest root(hdr);
        
        template <typename hdr, typename digest>
        digest parent(hdr);
        
        template <typename hdr, typename N>
        N cumulative_pow(list<hdr> lh) {
            struct pv {
                N Value;
                
                pv(hdr h) : Value{pow(h)} {}
                pv(N v) : Value(v) {}
                
                pv operator+(pv pp) const {
                    return pv{Value + pp.Value};
                }
            };
            
            return reduce(lh, pv{0}).Value;
        }
        
        template <typename tx, typename block, typename digest>
        inline bool contains(tx t, block b, merkle::tree<digest> d) {
            return merkle::check(merkle::root_to_leaf<digest>{root(b), hash(t)}, d);
        }
        
        template <typename I, typename P>
        inline bool check(I i, P p) {
            return contains(i.Transaction, i.Block, p);
        }
        
        // A statement that a transaction exists in a block. 
        template <typename tx, typename block>
        struct in {
            tx Transaction;
            block Block;
            
            in(tx t, block b) : Transaction{t}, Block{b} {}
        };
        
        template <typename proposition, typename derivation>
        proof<bool (*)(proposition, derivation), proposition, derivation> state(proposition p, derivation d) {
            return proof<bool (*)(proposition, derivation), proposition, derivation>{check<proposition, derivation>, p, d};
        }
        
        // type representing a proof that a transaction is in a block. 
        template <typename tx, typename hdr, typename digest>
        using proof = abstractions::proof<bool (*)(in<tx, hdr>, merkle::tree<digest>), in<tx, hdr>, merkle::tree<digest>>;
        
    }
    
} 

#endif
