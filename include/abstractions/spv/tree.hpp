#ifndef ABSTRACTIONS_SPV_BLOCKTREE_HPP
#define ABSTRACTIONS_SPV_BLOCKTREE_HPP

#include <abstractions/blockchain/header.hpp>
#include <abstractions/data.hpp>

namespace abstractions  {
    
    namespace block {

        template <typename digest, typename hdr>
        struct tree {
            header::parent<hdr, digest> Parent;
            header::hash<hdr, digest> Hash;

            // set of known headers referenced by digest. 
            map<digest, hdr> Headers;
            
            // set of digests for which no know children exist. 
            set<digest> Leaves;
            
            // map from hashes to list of headers referencing that hash as its parent
            // for which no known header exists having that hash. 
            map<digest, list<hdr>> Roots;
            
            bool valid() const {
                // Every digest in Leaves must be in Headers. 
                for (digest d : Leaves) if (!Headers.contains(d)) return false;
                
                // Every digest in Roots must not be in Headers. 
                for (digest d : Roots) if (Headers.contains(d)) return false;
                
                for (digest d : Headers) {
                    hdr h = Headers[d];
                    digest p = Parent(h);
                    
                    // No header in Headers can have any digest in Leaves as its parent. 
                    if (Leaves.contains(p)) return false;
                    
                    if (Headers.contains(p)) {
                        // If we know about the parent header, then p cannot be in Roots. 
                        if (Roots.contains(p)) return false;
                        
                        // Otherwise, the header must be indexed in Roots under the parent hash. 
                    } else if (!Roots[p].contains(h)) return false;
                }
                
                return true;
            }
            
            tree() {}
            
            tree(
                header::parent<digest, hdr> p,
                header::hash<hdr, digest> sh) : Parent(p), Hash(sh) {}
            
            const tree connect(hdr h) const {
                // Do we already know about this header? 
                if (Headers.contains(h)) return this;
                
                digest sh = hash(h);
                auto headers = Headers.insert(sh, h);
                
                // is this header the parant of some root header? 
                map<digest, list<hdr>> roots;
                set<digest> leaves;
                if (Roots.contains(sh)) {
                    roots = Roots.remove(sh);
                    leaves = Leaves;
                } else {
                    roots = Roots;
                    leaves = Leaves + sh;
                }
                
                // Do we know about this header's parent?
                digest p = get_parent(h);
                if (!Headers.contains(p)) return tree(Parent, Hash, roots.replace(p, roots[p] + h), leaves);
                
                return blocktree(Parent, Hash, roots, leaves.remove(p));
            }
            
            list<hdr> chain(digest viewpoint) {
                list<hdr> l{};
                for (hdr h = Headers[viewpoint]; h != hdr{}; h = Headers[Parent(h)]) l = l + h;
                return l;
            }
            
        private:
            tree(
                header::parent<digest, hdr> p,
                header::hash<hdr, digest> sh,
                map<digest, hdr> h,
                set<hdr> l, 
                map<digest, list<hdr>> r) : Parent(p), Hash(sh), Headers(h), Leaves(l), Roots(r) {}
        };
    
    }
    
} 

#endif
