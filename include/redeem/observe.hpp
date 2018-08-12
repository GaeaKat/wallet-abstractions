#ifndef REDEEM_OBSERVE_HPP
#define REDEEM_OBSERVE_HPP

#include<abstractions.hpp>

namespace abstractions
{

namespace redeem
{

template<typename tag, typename secret>
using identifier = tag (* const)(secret);

template<typename output, typename tag, typename secret>
using recognition = ℕ (* const)(identifier<tag, secret>, output);

template<typename output, typename tag, typename truth>
using observation = truth (* const)(ℕ, identifier<output, tag>, output, tag);

template<typename output, typename truth, typename tag, typename secret>
truth observe(
    observation<output, tag, truth> ob,
    recognition<output, tag, secret> r,
    identifier<tag, secret> id,
    output out,
    tag t)
{
    return ob(r(id, out), id, out, t);
}

}

}

#endif
