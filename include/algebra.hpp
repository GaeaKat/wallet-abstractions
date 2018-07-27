#ifndef HD_ALGEBRA_HPP
#define HD_ALGEBRA_HPP

namespace hd
{

// types for function pointers to fundamental operations.
    
// An algebra by which a new key can be derived from any given key. 
//   K - whatever the underlying implementation uses as a HD node.
//   M - whatever is used as the index of the key derivation,
//       most likely uint32_t for bip32. 
template<typename K, typename M>
using algebra = K (* const)(K, M);

// A function which transforms objects of type K to type P
// representing a public-key schema. 
template<typename K, typename P>
using to_public = P (* const)(K);

}

#endif
