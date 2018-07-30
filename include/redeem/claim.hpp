#ifndef REDEEM_CLAIM_HPP
#define REDEEM_CLAIM_HPP

namespace abstractions
{

namespace redeem
{

template<typename D>
struct requirement {
    virtual bool can_satisfy(D) const = 0;
};

template<typename... P>
struct proposition {
    virtual bool satisfies(P...) const = 0;
};

template<typename K, typename P>
using to_public = P (* const)(K);
template<typename K, typename A, typename Format>
using to_address = A (* const)(K, Format);

template<typename K, typename P, typename Database>
class is_private_of_public : public proposition<K> , public requirement<Database> {
    P pubkey;
public:
    bool satisfies(K k) const final override {
        pubkey == get_to_public()(k);
    }
    
    to_public<K, P> get_to_public() = 0;
    
    bool can_satisfy(Database d) const {
        d.template private_from_public<P>(pubkey);
    }
    
    is_private_of_public(P p) : pubkey(p) {}
};

template<typename K, typename A, typename T, typename Database>
class is_private_of_address : public proposition<K> , public requirement<Database> {
    A address;
    T address_type;
public:
    bool satisfies(K k) const final override {
        address == get_to_address()(k, address_type);
    }
    
    to_address<K, A, T> get_to_address() = 0;
    
    bool can_satisfy(Database d) const {
        d.template private_from_address<A>(address);
    }
    
    is_private_of_address(A a, T t) : address(a), address_type(t) {}
};

}

}

#endif
