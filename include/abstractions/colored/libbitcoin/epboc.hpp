#ifndef ABSTRACTIONS_COLORED_LIBBITCOIN_HPBOC_HPP
#define ABSTRACTIONS_COLORED_LIBBITCOIN_HPBOC_HPP

#include <abstractions/colored/epobc.hpp>
#include <bitcoin/bitcoin/chain/transaction.hpp>

namespace abstractions
{

    namespace colored
    {

        typedef const ::libbitcoin::hash_digest hash;

        template<> const hash null_color<hash> = ::libbitcoin::null_hash;

        typedef ::libbitcoin::chain::output output;
        typedef ::libbitcoin::chain::transaction transaction;
        typedef ::libbitcoin::chain::output_point outpoint;

        namespace low {

            // Implementations of this library must implement these next 5 functions. 
            template <typename tx>
            n_sequence first_n_sequence(transaction t) {
                return t.inputs()[0].sequence();
            }

            template <>
            inline colored::hash hash(transaction t) {
                return t.hash();
            }

            template <>
            inline vector<output> outputs(transaction t) {
                return t.outputs();
            }

            template <> 
            inline vector<outpoint> inputs(transaction t) {
                auto ins = t.inputs();
                std::vector<outpoint> outpoints(ins.size());
                for(int i = 0; i < ins.size(); i++) {
                    outpoints[i] = ins[i].previous_output();
                }
                return outpoints;
            }

            template <>
            inline N bitcoin_value(output o) {
                return o.value();
            }

        }

    }

}

#endif
