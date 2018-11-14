#ifndef ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/claim.hpp>

namespace abstractions
{
        
    namespace merkle
    {
        
        template <typename digest>
        using combine = digest (*const)(digest, digest);

        template <typename digest>
        struct node {
            virtual const digest hash(combine<digest> c) const = 0;
            
            virtual set<digest> depth(N n) const = 0;
        };
        
        template <typename digest>    
        struct leaf : public node<digest> {
            const digest& Digest;
        
            leaf(const digest& d) : Digest(d) {}
            
            const digest hash(combine<digest>) const final override {
                return Digest;
            }
            
            set<digest> depth(N n) const final override {
                if (n == 0) return Digest;
                return {};
            }
        };
        
        template <typename digest>    
        struct branch : public node<digest> {
            const node<digest>& Left;
            const node<digest>& Right;
            
            branch(const node<digest>& l, const node<digest>& r) : Left(l), Right(r) {}
                
            const digest hash(combine<digest> c) const final override {
                return c(Left.hash(c), Right.hash(c));
            }
            
            set<digest> depth(N n) const final override {
                return Left.depth(n - 1) + Right.depth(n - 1);
            }
        };
        
        template <typename digest>    
        struct odd_branch : public node<digest> {
            const node<digest>& Left;
            
            odd_branch(const node<digest>& l) : Left(l) {}
                
            const digest hash(combine<digest> c) const final override {
                return c(Left.hash(c), Left.hash(c));
            }
            
            set<digest> depth(N n) const final override {
                return Left.depth(n - 1);
            }
        };
        
        template <typename digest>
        struct partial {
            list<digest> Hashes;
            list<leaf<digest>> Leaves;
            list<branch<digest>> Branches;
            list<odd_branch<digest>> OddBranches;
            set<digest> Transactions;
            N Depth;
        
        private:
            node<digest>* Root;
            
            partial(list<digest> h, list<leaf<digest>> l, list<branch<digest>> b, list<odd_branch<digest>> ob, set<digest> t, N d, node<digest>* r)
                : Hashes(h), Leaves(l), Branches(b), OddBranches(ob), Transactions(t), Depth(d), Root(r) {}
            
        public:
            partial() : Root(nullptr) {}
            
            bool verify(digest root_hash, combine<digest> c) const {
                return (Root != nullptr) && root_hash == Root->hash(c) && Transactions == Root->depth(Depth);
            }
            
        };
        
        // Derivation that can be used to prove that a transaction is in a block. 
        template <typename digest>
        struct derivation {
            partial<digest> Tree;
            combine<digest> Combine;
            
            derivation(partial<digest> t, combine<digest> c) : Tree(t), Combine(c) {}
        };
        
        template <typename digest>
        struct root_to_leaf {
            digest Root;
            digest Leaf;
        };
    
        // A claim that two digests form the roof and leaf of a merkle tree is verified. 
        template <typename propositon, typename derivation>
        bool check(propositon p, derivation d) {
            return d.Tree.verify(p.Root, d.Combine) && contains(d.Tree.Transactions, p.Leaf);
        }
        
        template <typename proposition, typename derivation>
        proof<bool (*)(proposition, derivation), proposition, derivation> state(proposition p, derivation d) {
            return proof<bool (*)(proposition, derivation), proposition, derivation>{check<proposition, derivation>, p, d};
        }
        
    }

}

#endif
