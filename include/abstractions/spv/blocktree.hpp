#ifndef ABSTRACTIONS_SPV_BLOCKCHAIN_HPP
#define ABSTRACTIONS_SPV_BLOCKCHAIN_HPP

#include <abstractions/data.hpp>
#include <abstractions/blockchain/blockchain.hpp>
#include <abstractions/blockchain/header.hpp>
#include <abstractions/invalid.hpp>

namespace abstractions 
{

    template <typename digest, typename header>
    class blocktree {
        headers::parent<header, digest> get_parent;
        headers::hash<header, digest> hash;
        
    public:
        const map<digest, list<header>> Roots;
        
        const map<digest, header> Headers;
        
        const set<digest> Leaves;
        
        blocktree() : {}
        
        blocktree(
            headers::parent<digest, header> g,
            headers::hash<header, digest> sh) : get_parent(p), hash(sh) {}
        
        blocktree connect(header h) {
            // Do we already know about this header? 
            if (Headers.contains(h)) return this;
            
            digest sh = hash(h);
            headers = Headers.insert(sh, h);
            
            // is this header the parant of some root header? 
            map<digest, list<header>> roots;
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
            if (!Headers.contains(p)) return blocktree(get_parent, hash, roots.replace(p, roots[p] + h), leaves);
            
            return blocktree(get_parent, hash, roots, leaves.remove(p));
        }
        
    private:
        blocktree(
            headers::parent<digest, header> g,
            headers::hash<header, digest> sh,
            map<digest, list<header>> r, 
            map<digest, header> h,
            set<header> l, 
            set<header> u), get_parent(g), hash(sh), Roots(r), Headers(h), Leaves(l) {}
    };
    
} 

#endif

