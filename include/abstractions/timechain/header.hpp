// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_BLOCKCHAIN_HEADER
#define ABSTRACTIONS_BLOCKCHAIN_HEADER

#include <data/list.hpp>
#include <abstractions/abstractions.hpp>
#include <abstractions/work/work.hpp>

namespace abstractions::timechain {
        
    template <typename digest>
    const extern digest Genesis;

    namespace header {
        
        template <typename header, typename digest>
        struct interface {
        
            uint256 work(header& h) const {
                return h.work();
            }
            
            digest hash(header& h) const {
                return h.hash();
            }
            
            digest root(header h) const {
                return h.root();
            }
            
            digest parent(header& h) const {
                return h.parent();
            }
            
            work::target target(header& h) const {
                return h.target();
            }
            
        };
    
    }
    
} 

#endif
