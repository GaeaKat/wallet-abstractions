#ifndef ABSTRACTIONS_HD_ALGEBRA_HPP
#define ABSTRACTIONS_HD_ALGEBRA_HPP

namespace abstractions
{

namespace hd
{

// types for function pointers to fundamental operations.
    
// An algebra by which a new key can be derived from any given key. 
//   K - whatever the underlying implementation uses as a HD node.
//   M - whatever is used as the index of the key derivation,
//       most likely uint32_t for bip32. 
template<typename K, typename M>
using algebra = K (*)(K, M);

// useful for bip47. 
template<typename K, typename P>
using to_shared = P (*)(K, P);

}

}

#endif
