#ifndef ABSTRACTIONS_KEYPAIR_HPP
#define ABSTRACTIONS_KEYPAIR_HPP

#include "abstractions.hpp"

namespace abstractions
{
    
    template <typename S, typename P>
    using one_way = P (* const)(S);

}

#endif
