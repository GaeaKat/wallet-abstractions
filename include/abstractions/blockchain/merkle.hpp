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
            const digest hash(combine<digest>) const final override {
                return Digest;
            }
        };
        
        template <typename digest>    
        struct branch : public node<digest> {
            const node<digest>& Left;
            const node<digest>& Right;
                
            const digest hash(combine<digest> c) const final override {
                return c(Left.hash(c), Right.hash(c));
            }
        };
        
        template <typename digest>
        struct partial_tree {
            const combine<digest> Combine;
            const vector<digest> Hashes;
            const vector<leaf<digest>> Leaves;
            const vector<branch<digest>> Branches;
            const node<digest>& Root;
            const vector<digest&> Transactions;
            
            bool verify(digest root_hash) {
                return root_hash == Root.hash(Combine);
            }
        };
        
    }

}

#endif
