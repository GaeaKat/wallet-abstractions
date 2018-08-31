#ifndef ABSTRACTIONS_HD_BIP32_HPP
#define ABSTRACTIONS_HD_BIP32_HPP

#include <abstractions/hd/secp256k1.hpp>

namespace abstractions
{

    namespace hd
    {
        
        namespace bip32
        {
        
            typedef const uint32_t child_index;

            // in bip32, there are two kinds of derivations. Hardened and unhardened.
            // A transformation which is hardened is denoted by having the hardened_flag
            // set. In otherwords if it is larger than 2^31. 
            const child_index hardened_flag = 0x80000000;
        }
        
    }

}

#endif

