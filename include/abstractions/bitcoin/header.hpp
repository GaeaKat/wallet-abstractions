#ifndef ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP
#define ABSTRACTIONS_BLOCKCHAIN_HEADER_HPP

#include <data/list.hpp>
#include <abstractions/association.hpp>

namespace abstractions 
{
    
    namespace bitcoin
    {
    
        namespace header
        {
            
            template <typename digest>
            const digest Genesis;
            
            template <typename list, typename N>
            N cumulative_pow(list lh) {
                struct pv {
                    N Value;
                    
                    pv() : Value{} {}
                    
                    pv operator+(pv pp) const {
                        return pv{Value + pp.Value};
                    }
                };
                
                return reduce(lh, pv{0}).Value;
            }
            
            template <typename header, typename N>
            inline N work(header& h) {
                return h.work();
            }
            
            template <typename header, typename digest>
            inline digest hash(header& h) {
                return h.hash();
            }
            
            template <typename header, typename digest>
            inline digest root(header h) {
                return h.root();
            }
            
            template <typename header, typename digest>
            inline digest parent(header& h) {
                return h.parent();
            }
            
        }
    
    }
    
} 

#endif
