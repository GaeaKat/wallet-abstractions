#ifndef HD_LIBBITCOIN_BIP32_HPP
#define HD_LIBBITCOIN_BIP32_HPP

#include <bip32.hpp>
#include <heap.hpp>

#include <bitcoin/bitcoin/wallet/hd_private.hpp>

namespace abstractions
{

namespace hd
{

namespace libbitcoin
{

typedef bip32::child_index index;
typedef ::libbitcoin::wallet::hd_public hd_public;
typedef ::libbitcoin::wallet::hd_private hd_private;

const hd_public public_derive(const hd_public hd, index i) {
    return hd.derive_public(i);
}

const hd_private private_derive(const hd_private hd, index i) {
    return hd.derive_private(i);
}

algebra<const hd_public, index> public_algebra = &public_derive;

algebra<const hd_private, index> private_algebra = &private_derive;

// should be able to generate theories very easily out of these. 

// return theories initialized on the heap that the user has to delete
// when he's done with them. 
const error_theory<const hd_public, index>* const public_hd_tree(hd_public n) {
    return new heap<const hd_public, index>(public_algebra, n);
}

const error_theory<const hd_private, index>* const private_hd_tree(hd_private n) {
    return new heap<const hd_private, index>(private_algebra, n);
}

}

}

}

#endif
