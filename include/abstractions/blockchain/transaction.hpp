#ifndef ABSTRACTIONS_BLOCKCHAIN_TRANSACTION_HPP
#define ABSTRACTIONS_BLOCKCHAIN_TRANSACTION_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>
#include <abstractions/slice.hpp>

#include "blockchain.hpp"
#include "output.hpp"

namespace abstractions 
{
        
    namespace transaction
    {

        // outputs of a transaction. 
        template <typename tx, typename out>
        using outputs = slice<out> (*)(tx);
            
        // inputs of a transaction.
        template <typename tx, typename point>
        using outpoints = slice<point> (*)(tx);
            
        // how much is stored in a given input?
        template <typename tx, typename point, typename script>
        using inputs = map<point, script> (*)(tx);
        
        // a vertex represents the flow of bitcoins in the blockchain.
        // it is a transaction without input scripts. When a tx is
        // being hashed, the input scripts must be removed. This type
        // is an intermediate stage in that process. 
        template <typename index, typename out>
        struct vertex {
            slice<index> Outpoints;
            slice<out> Outputs;
            
            vertex(slice<index> in, slice<out> o) : Outpoints(in), Outputs(o) {}
        };
        
        template <typename tx, typename point, typename out>
        inline vertex<point, out> to_vertex(outputs<tx, out> ou, outpoints<tx, point> oi, tx t) {
            return vertex<point, out>(oi(t), ou(t));
        };
        
        template <typename tx, typename point, typename out>
        N redeemed(blockchain<point, out>& b, output::value<out> v, outpoints<tx, point> oi, tx t) {
            int r = 0;
            for (point p : oi(t))
            {
                out prevout = b(p);
                
                if (prevout == invalid<out>) return aleph_0;
                    
                r += v(prevout);
            }
            return r;
        }
        
        template <typename tx, typename point, typename out>
        inline N spent(output::value<out> v, outputs<tx, point> ou, tx t) {
            int r = 0;
            for (out p : ou(t)) r += v(p);
            return r;
        }
        
        template <typename tx, typename point, typename out>
        inline Z fee(blockchain<point, out>& b, output::value<out> v, outputs<tx, point> ou, outpoints<tx, point> oi, tx t) {
            Z redeemed = redeemed(b, v, oi, t);
            if (redeemed == aleph_0) return aleph_0;
            return redeemed - spent(v, ou, t);
        }

        template <typename tx, typename point, typename out>
        inline bool positive(blockchain<point, out>& b, output::value<out> v) {
            return fee(b, v) > 0;
        }
    
    }
    
} 

#endif

