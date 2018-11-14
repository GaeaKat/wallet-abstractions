#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HEADER_HPP

#include <abstractions/list.hpp>
#include <abstractions/data.hpp>

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
        
        template <typename digest, typename hdr>
        struct header {
            N Height;
            hdr Header;
            digest Digest;
            
            header(digest Genesis) : Digest{Genesis}, Height{0}, Header{} {}
        
        private:
            header(N h, hdr hh, digest d) : Height{h}, Header{hh}, Digest{d} {}
        };
        
        template <typename digest, typename hdr, typename hash, typename parent>
        struct chain {
            
            digest Genesis;
            
            parent Parent;
            
            hash Hash;
            
            using sequence = list<header<digest, hdr> >;
            
            sequence Chain;
            
            map<digest, sequence> Header;
            
            map<N, sequence> Height;
            
            chain(digest g, parent p, hash h) : Genesis{g}, Parent{p}, Hash{h} {}
            chain() {}
            
            header<digest, hdr> latest() const {
                if (empty(Header)) return hdr{Genesis};
                
                return first(Header);
            };
            

        private:
            chain(digest g, parent p, hash h, sequence c, map<digest, sequence> hs, map<N, sequence> ht)
                : Genesis{g}, Parent{p}, Hash{h}, Chain{c}, Header{hs}, Height{ht} {}
            
        public:
            chain operator+(hdr h) const {
                header<digest, hdr> l = latest();
                if (l.Digest == Parent(h)) {
                    block::header<digest, hdr> hh{l.Height + 1, h, Hash(h)};
                    sequence next = Chain + hh;
                    return chain(Genesis, Parent, Hash, next, Header.insert(hh.Digest, next), Height.insert(hh.Height, next));
                }
                return chain();
            }
        };
        
    }
    
} 

#endif
