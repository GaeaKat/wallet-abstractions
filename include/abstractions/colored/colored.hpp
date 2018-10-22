#ifndef ABSTRACTIONS_COLORED_COLORED_HPP
#define ABSTRACTIONS_COLORED_COLORED_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions
{

    namespace colored
    {
        
        template <typename T, typename C>
        using color = C (*) (T tx);
        
        enum tx_type {none, genesis, mint, send};
        
        template <typename T, typename C>
        using get_type = tx_type (*)(T);
        
        template <typename color_type>
        struct colored_value {
            N Value;
            color_type Color;
            
            colored_value() : Value(0), Color({}) {}
            
            // You're not allowed to have colored value with zero in it. 
            colored_value(N v, color_type c) : Value(c == 0 ? 0 : v), Color(v == 0 ? 0 : c) {}
        };

        template <typename outpoint, typename tx, typename output, typename color_type>
        struct blockchain;

        template <typename outpoint, typename tx, typename output, typename color_type>
        struct colored_output {
            N Index;
            tx Transaction;
            
            const colored_value<color_type> value(blockchain<outpoint, tx, output, color_type>&);
            
            bool valid() {
                return Index != aleph_0;
            }
            
            colored_output() : Index(aleph_0), Transaction() {}
            colored_output(N i, tx t) : Index(i), Transaction(t) {}
        };

        // Implementations of this library must provide a blockchain implementation. 
        template <typename outpoint, typename tx, typename output, typename color_type>
        struct blockchain {
            virtual colored_output<outpoint, tx, output, color_type> get_output(outpoint) const = 0;
            
            // Can be overridden if you want to cache values. 
            // Otherwise you'd have to run down the blockchain every 
            // time you wanted to compute values. 
            virtual colored_value<color_type> value(outpoint o) const {
                return get_output(o).value(*this);
            };
        };

        template <typename output, typename tx, typename outpoint, typename color_type> 
        inline const colored_value<color_type> value(outpoint p, const blockchain<outpoint, tx, output, color_type>& b) {
            return b.colored_output(p).value(b);
        }

        template<typename outpoint, typename tx, typename output, typename color_type>
        colored_value<color_type> value(tx, N index, blockchain<outpoint, tx, output, color_type>& b);

        template <typename outpoint, typename tx, typename output, typename color_type>
        inline const colored_value<color_type> colored_output<outpoint, tx, output, color_type>::value(
            blockchain<outpoint, tx, output, color_type>& b) {
            if (!valid()) return 0;
            return colored::value<outpoint, tx, output, color_type>(Transaction, Index, b);
        }
        
    }

}

#endif
