#ifndef ABSTRACTIONS_COLORED_HPBOC_HPP
#define ABSTRACTIONS_COLORED_HPBOC_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions
{

    namespace colored
    {
        // Implementations of this library must provide a null color. 
        template <typename color_type>
        extern const color_type null_color;
        
        template <typename color_type>
        struct colored_value {
            N Value;
            color_type Color;
            
            colored_value() : Value(0), Color(null_color<color_type>) {}
            
            // You're not allowed to have colored value with zero in it. 
            colored_value(N v, color_type c) : Value(c == null_color<color_type> ? 0 : v), Color(v == 0 ? null_color<color_type> : c) {}
        };

        template <typename color_type>
        const colored_value<color_type> zero();

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
            if (!valid()) return zero;
            return colored::value<outpoint, tx, output, color_type>(Transaction, Index, b);
        }

        typedef uint32_t n_sequence;

        const n_sequence epobc_transfer = 0x33;
        const n_sequence epobc_genesis = 0x25;

        const n_sequence epobc_transaction_type_mask = 0b111111;
        const n_sequence epobc_padding_mask = (0 - 1) - epobc_transaction_type_mask;
        
        namespace low {

            // Implementations of this library must implement these next 5 functions. 
            template <typename tx>
            n_sequence first_n_sequence(tx);

            template <typename tx, typename color_type>
            color_type hash(tx);
            
            template <typename output, typename tx>
            vector<output> outputs(tx);
            
            template <typename outpoint, typename tx>
            vector<outpoint> inputs(tx);

            template <typename output>
            N bitcoin_value(output);

            template <typename tx>
            inline n_sequence transaction_type(tx t) {
                return first_n_sequence(t) & epobc_transaction_type_mask;
            }

            template <typename tx>
            inline N padding(tx t) {
                n_sequence x = (n_sequence(t) & epobc_padding_mask) >> 6;
                if (x == 0) return 0;
                return 1 << x;
            }
            
        }

        template<typename outpoint, typename tx, typename output, typename color_type>
        colored_value<color_type> value(tx t, N index, blockchain<outpoint, tx, output, color_type>& b) {
            switch (transaction_type(t)) {
            default : 
                return zero;

            case epobc_genesis : 
                if (index != 0) return zero;
                return colored_value<color_type>(
                    bitcoin_value(outputs(t)[0]) - low::padding<tx>(t),
                    low::hash<tx, color_type>(t));

            case epobc_transfer : 
                vector<output> outs = outputs(t);
                if (outs.size() <= index) return zero;

                N p = low::padding<tx>(t);
                std::vector<int64_t> output_values_minus_padding(index + 1);
                for (int i = 0; i <= index; i++) {
                    output_values_minus_padding[i] = outs[i] - p;
                        
                    if (output_values_minus_padding[i] < 0) return zero;
                }

                // This part of the protocol was so confusing in the
                // source I read here 
                //     https://github.com/chromaway/ngcccbase/wiki/EPOBC_simple
                // that I'm pretty sure I got it right but I would
                // like to be able to do more to make sure. 
                vector<outpoint> ins = inputs(t);
                int output_index = 0;
                int running_input_value_total = 0;
                color_type last = null_color<color_type>;
                for (outpoint op : ins) {
                    colored_value<color_type> v = b.value();
                    if (v == zero) return zero;
                    
                    if (last == null_color<color_type>) last = v.Color;
                    else if (last != v.Color) return zero;
                    
                    running_input_value_total += v;
                    if (running_input_value_total < output_values_minus_padding[output_index]) continue;
                    
                    if (output_index == index) break;
                    
                    if (running_input_value_total == output_values_minus_padding[output_index]) last == null_color<color_type>;
                    
                    running_input_value_total -= output_values_minus_padding[output_index];
                }
                
                return colored_value<color_type>(output_values_minus_padding[index], last);
            }
        }
        
    }
    
} 

#endif
