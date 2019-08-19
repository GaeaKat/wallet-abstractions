// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_CRYPTO_ADDRESS
#define ABSTRACTIONS_CRYPTO_ADDRESS

#include <data/crypto/one_way.hpp>

namespace abstractions::crypto {
    
    // template specialize this if you have your
    // own definition of the sign for your types. 
    template <typename addr, typename pk> 
    struct address : data::function::abstract<addr, pk> {
        address() = delete;
        
        addr operator()(pk s) const final override;
    };
    
    template <typename sk, typename pk, typename addr> 
    struct address_scheme : public data::crypto::keypair<sk, pk> {
        addr address(const pk s) const;
    };
    
} 

#endif
