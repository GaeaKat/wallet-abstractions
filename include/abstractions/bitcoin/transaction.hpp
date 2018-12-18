#ifndef ABSTRACTIONS_BITCOIN_TRANSACTION_HPP
#define ABSTRACTIONS_BITCOIN_TRANSACTION_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/bitcoin/output.hpp>

namespace abstractions 
{
    
    namespace bitcoin
    {
        
        namespace transaction
        {

            // outputs of a transaction. 
            template <typename tx, typename out>
            inline slice<out> outputs(tx t) {
                return t.outputs();
            }
                
            // inputs of a transaction.
            template <typename tx, typename in>
            inline slice<in> inputs(tx t) {
                return t.inputs();
            }
                
            // inputs of a transaction.
            template <typename tx, typename digest>
            inline digest hash(tx t) {
                return t.hash();
            }
            
            template <typename point, typename tx>
            using index = association<point, tx>;
            
            template <typename tx, typename index, typename point, typename out>
            N redeemed(index b, tx t) {
                int r = 0;
                for (point p : outpoints(t))
                {
                    out prevout = b(p);
                    
                    if (prevout == out{}) return aleph_0;
                        
                    r += output::value(prevout);
                }
                return r;
            }
            
            template <typename tx, typename point, typename out>
            inline N spent(tx t) {
                int r = 0;
                for (out p : outputs(t)) r += output::value(p);
                return r;
            }
            
            template <typename tx, typename index>
            inline Z fee(index b, tx t) {
                Z redeemed = redeemed(b, t);
                if (redeemed == invalid<Z>) return invalid<Z>;
                return redeemed - spent(t);
            }

            template <typename tx, typename index>
            inline bool positive(tx t, index b) {
                return fee(t, b) > 0;
            }
        
        }
        
    }
    
} 

#endif

