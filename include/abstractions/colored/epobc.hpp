#ifndef ABSTRACTIONS_COLORED_HPBOC_HPP
#define ABSTRACTIONS_COLORED_HPBOC_HPP

#include <abstractions/colored/colored.hpp>

namespace abstractions
{

    namespace colored
    {
        
        namespace epobc {

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
                    return 0;

                case epobc_genesis : 
                    if (index != 0) return 0;
                    return colored_value<color_type>(
                        bitcoin_value(outputs(t)[0]) - low::padding<tx>(t),
                        low::hash<tx, color_type>(t));

                case epobc_transfer : 
                    vector<output> outs = outputs(t);
                    if (outs.size() <= index) return 0;

                    N p = low::padding<tx>(t);
                    std::vector<int64_t> output_values_minus_padding(index + 1);
                    for (int i = 0; i <= index; i++) {
                        output_values_minus_padding[i] = outs[i] - p;
                            
                        if (output_values_minus_padding[i] < 0) return 0;
                    }

                    // This part of the protocol was so confusing in the
                    // source I read here 
                    //     https://github.com/chromaway/ngcccbase/wiki/EPOBC_simple
                    // that I'm pretty sure I got it right but I would
                    // like to be able to do more to make sure. 
                    vector<outpoint> ins = inputs(t);
                    int output_index = 0;
                    int running_input_value_total = 0;
                    color_type last = {};
                    for (outpoint op : ins) {
                        colored_value<color_type> v = b.value();
                        if (v == 0) return 0;
                        
                        if (last == 0) last = v.Color;
                        else if (last != v.Color) return 0;
                        
                        running_input_value_total += v;
                        if (running_input_value_total < output_values_minus_padding[output_index]) continue;
                        
                        if (output_index == index) break;
                        
                        if (running_input_value_total == output_values_minus_padding[output_index]) last == 0;
                        
                        running_input_value_total -= output_values_minus_padding[output_index];
                    }
                    
                    return colored_value<color_type>(output_values_minus_padding[index], last);
                }
                
            }
            
        }
        
    }
    
} 

#endif
