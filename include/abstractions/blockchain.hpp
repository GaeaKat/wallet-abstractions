#ifndef ABSTRACTIONS_REDEEM_BLOCKCHAIN_HPP
#define ABSTRACTIONS_REDEEM_BLOCKCHAIN_HPP

namespace abstractions 
{
        
    template <typename outpoint, typename output>
    struct blockchain {
        virtual output operator()(outpoint) const = 0;
    };
    
} 

#endif

