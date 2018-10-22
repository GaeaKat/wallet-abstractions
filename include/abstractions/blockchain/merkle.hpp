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
        };
        
        template <typename digest>    
        struct leaf : public node<digest> {
            const digest& Digest;
        
            leaf(const digest& d) : Digest(d) {}
            
            const digest hash(combine<digest>) const final override {
                return Digest;
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
        };
        
        template <typename digest>    
        struct odd_branch : public node<digest> {
            const node<digest>& Left;
            
            odd_branch(const node<digest>& l) : Left(l) {}
                
            const digest hash(combine<digest> c) const final override {
                return c(Left.hash(c), Left.hash(c));
            }
        };
        
        template <typename digest>
        struct partial_tree {
            const list<digest> Hashes;
            const list<leaf<digest>> Leaves;
            const list<branch<digest>> Branches;
            const list<odd_branch<digest>> OddBranches;
            const list<digest&> Transactions;
            const node<digest>* Root;
            
            partial_tree() : Root(nullptr) {}
            partial_tree(list<digest> h, list<leaf<digest>> l, list<branch<digest>> b, list<odd_branch<digest>> ob, list<digest&> t, node<digest>* r)
                : Hashes(h), Leaves(l), Branches(b), OddBranches(ob), Transactions(t), Root(r) {}
            
            bool verify(digest root_hash, combine<digest> c) {
                if (Root == nullptr) return false;
                return root_hash == Root->hash(c);
            }
        };
        
    }

}

#endif
