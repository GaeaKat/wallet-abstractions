#ifndef ABSTRACTIONS_BITCOIN_CACHED_HEADER_HPP
#define ABSTRACTIONS_BITCOIN_CACHED_HEADER_HPP

#include <abstractions/bitcoin/header.hpp>

namespace abstractions 
{
    
    namespace bitcoin {
    
        namespace header {
            
            // A header that caches the result of calculating its hash. 
            template <typename H, typename N, typename digest>
            struct cached {
                H Header;
                
                N pow() const {
                    if (Work == 0) Work = pow(Header);
                    return Work;
                }
                
                const digest hash() const {
                    if (Digest == digest{}) Digest = hash(Header);
                    
                    return Digest;
                }
                
                inline const digest root() const {
                    return root(Header);
                }
                
                inline const digest parent() const {
                    return parent(Header);
                } 
                
                cached(H h) : Header{h}, Digest{} {}
                
            private:
                mutable digest Digest;
                mutable N Work;
            };
            
        } 
    
    }

}

#endif
