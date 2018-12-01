#ifndef ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/claim.hpp>

namespace abstractions
{
        
    namespace merkle
    {
        
        // A function to combine two digests and return a new digest. 
        template <typename digest>
        digest combine(digest, digest);
        
        template <typename digest> struct node;
        
        template <typename digest>
        using tree = pointer<node<digest>>;

        // A node in a Merkle tree. 
        template <typename digest>
        struct node {
            virtual const digest hash() const = 0;
            
            virtual set<digest> get_at_depth(N n) const = 0;
            
            virtual N depth() const = 0;
            
            virtual tree<digest> left() const = 0;
            
            virtual tree<digest> right() const = 0;
        };
        
        template <typename digest>    
        struct leaf : public node<digest> {
            const digest Digest;
        
            leaf(const digest d) : Digest(d) {}
            
            const digest hash() const final override {
                return Digest;
            }
            
            set<digest> get_at_depth(N n) const final override {
                if (n == 0) return Digest;
                return {};
            }
            
            N depth() const final override {
                return 0;
            };
            
            virtual tree<digest> left() const final override {
                return nullptr;
            };
            
            virtual tree<digest> right() const final override {
                return nullptr;
            };
        };
        
        template <typename digest>    
        class branch : public node<digest> {
            mutable digest Digest;
            
        public:
            const node<digest>& Left;
            const node<digest>& Right;
            
            branch(const node<digest>& l, const node<digest>& r) : Left(l), Right(r), Digest{} {}
                
            const digest hash() const final override {
                if (Digest == digest{}) Digest = combine(Left.hash(), Right.hash());
                return Digest;
            }
            
            set<digest> get_at_depth(N n) const final override {
                return Left.get_at_depth(n - 1) + Right.get_at_depth(n - 1);
            }
            
            N depth() const final override {
                return std::max(Left.depth(), Right.depth()) + 1;
            };
            
            virtual tree<digest> left() const final override {
                return Left;
            };
            
            virtual tree<digest> right() const final override {
                return Right;
            };
        };
        
        template <typename digest>    
        class odd_branch : public node<digest> {
            mutable digest Digest;
            
        public:
            const node<digest>& Left;
            
            odd_branch(const node<digest>& l) : Left(l), Digest{} {}
                
            const digest hash() const final override {
                if (Digest == digest{}) Digest = combine(Left.hash(), Left.hash());
                return Digest;
            }
            
            set<digest> get_at_depth(N n) const final override {
                return Left.get_at_depth(n - 1);
            }
            
            N depth() const final override {
                return Left.depth() + 1;
            }
            
            virtual tree<digest> left() const final override {
                return Left;
            };
            
            virtual tree<digest> right() const final override {
                return Left;
            };
        };
        
        template <typename digest>
        inline N depth(tree<digest> t) {
            return t->depth();
        }
        
        template <typename digest>
        inline set<digest> transactions(tree<digest> t) {
            return t->get_at_depth(depth(t));
        }
        
        template <typename digest>
        inline N size(tree<digest> t) {
            return size(transactions(t));
        }
        
        template <typename digest>
        inline bool member(tree<digest> t, digest m) {
            return contains(transactions(t), m);
        }
        
        // prune a tree by the given set. 
        template <typename digest>
        tree<digest> prune(tree<digest> m, set<digest> txs);
        
        // merge two trees together. 
        template <typename digest>
        tree<digest> merge(tree<digest> p, tree<digest> p2);
        
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
            
            bool verify(digest root_hash) const {
                return (Root != nullptr) && root_hash == Root->hash() && Transactions == Root->depth(Depth);
            }
            
        };
        
    }

}

#endif
