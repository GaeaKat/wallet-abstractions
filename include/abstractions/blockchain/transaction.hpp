#ifndef ABSTRACTIONS_BLOCKCHAIN_TRANSACTION_HPP
#define ABSTRACTIONS_BLOCKCHAIN_TRANSACTION_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions 
{
        
    namespace transaction
    {

        // outputs of a transaction. 
        template <typename tx, typename out>
        slice<out> outputs(tx);
            
        // inputs of a transaction.
        template <typename tx, typename point>
        slice<point> outpoints(tx);
            
        // how much is stored in a given input?
        template <typename tx, typename point, typename script>
        map<point, script> inputs(tx);
        
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

#endif

