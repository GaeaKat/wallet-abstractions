#ifndef ABSTRACTIONS_BITCOIN_MERKLE_HPP
#define ABSTRACTIONS_BITCOIN_MERKLE_HPP

#include <abstractions/claim.hpp>

namespace abstractions {
    
    namespace merkle {
        
        // check that a tree has the given root. 
        template <typename tree, typename digest>
        inline bool check_root(tree t, digest r) {
            return r == t.root();
        }
        
        // check that a tree has the given leaf. 
        template <typename tree, typename digest>
        inline bool check_leaf(tree t, digest l) {
            return t.contains(l);
        }
        
        // construct a proof that a merkle tree has a given root. 
        template <typename digest, typename tree>
        using root_proof = abstractions::proof<bool (*)(digest, tree), digest, tree>;
        
        template <typename digest, typename tree>
        inline const root_proof<digest, tree> state_root_proof(digest r, tree t) {
            return {check_root, r, t};
        }
        
        // construct a proof that a merkle tree has a given leaf. 
        template <typename digest, typename tree>
        using leaf_proof = abstractions::proof<bool (*)(digest, tree), digest, tree>;
        
        template <typename digest, typename tree>
        inline const leaf_proof<digest, tree> state_leaf_proof(digest r, tree t) {
            return leaf_proof<digest, tree>{check_leaf, r, t};
        }
        
        // A claim that a particular tree exists which has the given root and leaf. 
        template <typename digest>
        struct root_to_leaf {
            digest Root;
            digest Leaf;
        };
    
        // A claim that two digests form the roof and leaf of a merkle tree is verified. 
        template <typename digest, typename tree>
        inline bool check(root_to_leaf<digest> p, tree t) {
            return check_root(t, p.Root) && check_leaf(t, p.Leaf);
        }
        
        template <typename digest, typename tree>
        using member_proof = abstractions::proof<bool (*)(root_to_leaf<digest>, tree), root_to_leaf<digest>, tree>;
        
        // construct a proof that a merkle tree has a given leaf. 
        template <typename digest, typename tree>
        inline const member_proof<digest, tree> state_member_proof(root_to_leaf<digest> claim, tree t) {
            return member_proof<digest, tree>{check, claim, t};
        }
        
        template <typename digest, typename tree>
        struct proof_generator {
            digest Root;
            tree Tree;
            bool Valid;
            
            bool valid() const {
                return Valid;
            }
            
            proof_generator(digest r, tree t) : Root{r}, Tree{t}, Valid{check_root(t, r)} {}
            
            member_proof<digest, tree> make_proof(digest tx) const {
                if (!Valid || Tree.contains(tx)) return {};
                return state_member_proof(root_to_leaf<digest>{Root, tx}, Tree.prune(tx));
            }
            
            // merge this proof generator with more information about the full merkle tree. 
            proof_generator<digest, tree> operator+(tree t) const {
                return proof_generator(Root, Tree + t);
            }
            
        private:
            proof_generator(digest r, tree t, bool v) : Root{r}, Tree{t}, Valid{v} {}
        };

    }
    
}

#endif 
