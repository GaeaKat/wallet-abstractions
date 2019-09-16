// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_VALUE
#define ABSTRACTIONS_VALUE

namespace abstractions {
    
    namespace meta {
        
        template <typename X>
        struct value {
            bool operator()(const X x) const {
                return x.value();
            }
        };
    
    }

    template <typename X>
    inline bool value(X x) {      
        return meta::value<X>{}(x);
    }

}

#endif
