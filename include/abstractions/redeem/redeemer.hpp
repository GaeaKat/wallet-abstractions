#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include <abstractions/blockchain/output.hpp>
#include <abstractions/blockchain/transaction.hpp>

namespace abstractions 
{
    
    namespace redeem
    {
        // a vertex represents the flow of bitcoins in the blockchain.
        // it is a transaction without input scripts. When a tx is
        // being hashed, the input scripts must be removed. This type
        // is an intermediate stage in that process. 
        template <typename index, typename out>
        struct vertex {
            slice<index> Outpoints;
            slice<out> Outputs;
            
            vertex(slice<index> in, slice<out> o) : Outpoints(in), Outputs(o) {}
            
            template <typename tx>
            vertex(tx t) : Outpoints(outpoints(t)), Outputs(outputs(t)) {}
        };
        
        template <typename script, typename outpoint, typename out>
        struct word {
            virtual script speak(N value, script prev, const vertex<outpoint, out> tx, uint32_t input_index) const = 0;
        };
        
        template <typename script, typename outpoint, typename out>
        using thought = pointer<const word<script, outpoint, out>>;
        
        template <typename script>
        using prepend_script = script (*const)(script, script);

        template <
            typename tx,
            typename script,   // means of redemption. 
            typename point,       // way if indexing a previous output. 
            typename out, 
            typename will>           // a desired outcome. 
        class redeemer {
            
            prepend_script<script> prepend;
            
            const blockchain<script, point>& prior;
            
            virtual thought<script,  point, out> how(script, will) const = 0;
            
        public:
            redeemer(
                blockchain<script, point>& b) 
            : prior(b) {}
            
            script redeem(tx t, point o, script in, will w) {
                // What is the index of the outpoint we want to redeem?
                vector<point> outpoints = get_outpoints(t);
                uint32_t index = 0;
                for (; index < outpoints.size(); index++) if (outpoints[index] == o) break;
                if (index == outpoints.size()) return script();
                
                // What's the previous output?
                out prevout = prior(o);
                if (prevout == out()) return script();
                
                // Can we really do this? 
                thought<script, point, out> hypothetical = how(Prepend(prevout->Pubkey, in), w);
                if (hypothetical == nullptr) return script();
                
                // Speak the magic word! 
                return Prepend(in, hypothetical->speak(get_value(*prevout), get_script(*prevout), transaction::to_vertex(t), index));
            }
            
            script redeem(tx t, point o, will w) {
                return redeem(t, o, w, script());
            }

            const map<point, script> spend(tx t, point o, will w) const {
                map<point, script> m;
                for (point o : t.Vertex.Outpoints) m = add(m, o, redeem(t, o, get_input_scripts(t)[o], w));
                return m;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
