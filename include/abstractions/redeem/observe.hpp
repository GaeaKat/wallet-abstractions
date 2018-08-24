#ifndef ABSTRACTIONS_REDEEM_OBSERVE_HPP
#define ABSTRACTIONS_REDEEM_OBSERVE_HPP

#include<abstractions/abstractions.hpp>

namespace abstractions
{

    namespace redeem
    {
        template <typename script>
        using pattern = bool (*)(script);

        template <typename script, typename tag, typename secret>
        ℕ recognize(map<ℕ, pattern<script>> m, script o) {
            for (ℕ n : m) if (m[n](o)) return n;
        }

        template <typename tag, typename script>
        using tags = vector<tag> (*)(script);

        template <typename secret, typename tag>
        struct database {
            pointer<secret> retrieve(tag);
        };

        // What is true of an output that has a given pattern and for which
        // we can produce the given set of tags which are found in it? 
        template <typename script, typename tag>
        using observation = knowledge (*)(pattern<script>, vector<tag>);

        // whether to observe a given output.
        template <typename truth, typename tag, typename secret, typename script>
        truth observe(
            observation<script, tag> ob,
            map<ℕ, pattern<script>> m,
            map<pattern<script>, vector<tags<tag, script>>> t,
            memory<secret, tag> d, 
            script out
        ) {
            ℕ n = recognize(m, out);
            pattern<script> p = m[n];
            std::vector<tags<tag, script>> have;
            for (tags<tag, script> c : t[p]) {
                tag t = c(out);
                if (d.retrieve(t) != nullptr) have.push_back(t);
            }
            return ob(m[n], have);
        }

    }

}

#endif
