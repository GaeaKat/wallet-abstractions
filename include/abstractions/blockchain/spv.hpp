#ifndef ABSTRACTIONS_BLOCKCHAIN_SPV_HPP
#define ABSTRACTIONS_BLOCKCHAIN_SPV_HPP

#include <abstractions/one_way.hpp>
#include "blockchain.hpp"
#include "merkle.hpp"

namespace abstractions
{

    namespace spv
    {
        
        template <typename tag, typename m>
        using hash = one_way<m, tag>;
        
    }

}

#endif
