#ifndef ABSTRACTIONS_REDEEM_OBSERVE_HPP
#define ABSTRACTIONS_REDEEM_OBSERVE_HPP

#include<abstractions/abstractions.hpp>

namespace abstractions
{

    namespace redeem
    {

        template<typename script>
        using pattern = bool (*)(script);

        template<typename script, typename tag, typename secret>
        N recognize(map<N, pattern<script>> m, script o) {
            for (N n : m) if (m[n](o)) return n;
        }

        template<typename tag, typename script>
        using tags = vector<tag> (*)(script);

        template<typename tag>
        struct memory {
            bool exists(tag);
        };

        // What is true of an output that has a given pattern and for which
        // we can produce the given set of tags which are found in it? 
        template<typename truth, typename pattern, typename tag>
        using observation = truth (*)(pattern, vector<tag>);

        // whether to observe a given output.
        template<typename truth, typename tag, typename secret, typename script>
        truth observe(
            observation<truth, pattern<script>, tag> ob,
            map<N, pattern<script>> m,
            map<pattern<script>, vector<tags<tag, script>>> t,
            memory<tag> d, 
            script out)
        {
            N n = recognize(m, out);
            pattern<script> p = m[n];
            std::vector<tags<tag, script>> have;
            for (tags<tag, script> c : t[p]) {
                tag t = c(out);
                if (d.exists(t)) have.push_back(t);
            }
            return ob(m[n], have);
        }

    }

}

#endif
