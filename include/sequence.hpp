#ifndef HD_SEQUENCE_HPP
#define HD_SEQUENCE_HPP

#include <hd.hpp>
#include <bip32.hpp>

namespace hd_tools
{
    
typedef bip32::child_index index;

template<typename Q>
class sequence {
    typedef typename theory<Q, index>::key key;
    
    index sequence_number;
public:
    const key& next() {
        sequence_number++;
        return this->operator[](sequence_number);
    }
    
    virtual const key& operator[](index i) = 0;
    
    sequence() : sequence_number(0) {}
    sequence(index n) : sequence_number(n) {}
};

template<typename Q>
class hd_sequence : sequence<Q> {
    typedef typename theory<Q, index>::key key;
    
    const theory<Q, index>& hd;
    const key& initial;
public:
    const key& operator[](index i) {
        return initial->child(i);
    }
    
    hd_sequence(const key& i) : sequence<Q>(), initial(i)  {}
    hd_sequence(const key& i, index n) : sequence<Q>(n), initial(i) {}
};

}

#endif 
