#ifndef HD_WALLET_HPP
#define HD_WALLET_HPP

namespace hd_tools
{

template<typename K, typename U>
struct wallet {
    bool has_balance(K k);
    U balance(K k);
};

}

#endif
