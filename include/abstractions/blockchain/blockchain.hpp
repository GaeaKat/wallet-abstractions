#ifndef ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP
#define ABSTRACTIONS_BLOCKCHAIN_BLOCKCHAIN_HPP

namespace abstractions 
{
        
    template <typename point, typename out>
    struct blockchain {
        virtual out operator[](point) const = 0;
    };
    
} 

#endif
