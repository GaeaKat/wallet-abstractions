#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include <abstractions/blockchain/output.hpp>
#include <abstractions/blockchain/blockchain.hpp>

namespace abstractions 
{
    namespace redeem
    {
        
        // a vertex represents the flow of bitcoins in the blockchain.
        // We don't need to know about the outputs, so there's just
        // one value that represents all outputs together. There's also
        // a list of links to other locations in the blockchain. 
        template <typename index, typename out>
        struct vertex {
            vector<index> Outpoints;
            vector<out> Outputs;
            
            vertex(vector<index> in, vector<out> o) : Outpoints(in), Outputs(o) {}
            
            N value(output::value<out> v) {
                int so_far = 0;
                for(out o : Outputs) so_far += v(o);
                return so_far;
            }
        };
        
        template <typename script, typename outpoint, typename out>
        struct word {
            virtual script speak(N value, script prev, vertex<outpoint, out> tx, uint32_t input_index) const = 0;
        };
        
        template <typename script, typename outpoint, typename out>
        using thought = pointer<const word<script, outpoint, out>>;

        template <typename script, typename outpoint, typename out>
        struct transaction{
            const vertex<outpoint, out> Vertex;
            map<outpoint, script> Incoming;

            N amount_transferred(blockchain<outpoint, out>& b, output::value<out> v) const {
                int r = 0;
                for (outpoint o : Vertex.Outpoints)
                {
                    out prevout = b(o);
                    
                    if (prevout == out()) return aleph_0;
                    
                    r += v(prevout);
                }
                return r;
            }
            
            N fee(blockchain<outpoint, out>& b, output::value<out> v) const {
                N transferred = amount_transferred(b);
                if (transferred == aleph_0) return aleph_0;
                return transferred - Vertex.value(v);
            }

            bool positive(blockchain<outpoint, out>& b, output::value<out> v) const {
                return fee(b, v) > 0;
            }
            
            transaction(const vertex<outpoint, out> x, map<outpoint, script> m) : Vertex(x), Incoming(m) {}
        };
        
        template <typename script>
        using prepend_script = script (*const)(script, script);

        template <
            typename script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename out, 
            typename will>           // a desired outcome. 
        class redeemer {
            output::value<out> get_value;
            output::script<out, script> get_script;
            prepend_script<script> prepend;
            const blockchain<script, outpoint>& prior;
            
            virtual thought<script, outpoint, out> how(script, will) const = 0;
            
        public:
            redeemer(
                output::value<out> ov,
                output::script<out, script> os,
                prepend_script<script> p,
                blockchain<script, outpoint>& b) : get_value(ov), get_script(os), prepend(p), prior(b) {}
            
            script redeem(vertex<outpoint, out> v, outpoint o, script in, will w) {
                // What is the index of the outpoint we want to redeem?
                uint32_t index = 0;
                for (; index < v.size(); index++) if (v[index] == o) break;
                
                // What's the previous output?
                out prevout = prior(o);
                if (prevout == out()) return script();
                
                // Can we really do this? 
                thought<script, outpoint, out> hypothetical = how(Prepend(prevout->Pubkey, in), w);
                if (hypothetical == nullptr) return script();
                
                // Speak the magic word! 
                return Prepend(in, hypothetical->speak(get_value(*prevout), get_script(*prevout), v, index));
            }
            
            script redeem(vertex<outpoint, out> v, outpoint o, will w) {
                return redeem(v, o, w, script());
            }

            const transaction<script, outpoint, out> spend(
                const transaction<script, outpoint, out> t, 
                will w
            ) const {
                std::map<outpoint, script> m;
                for (outpoint o : t.Vertex.Outpoints) 
                    m.insert(std::make_pair(o, redeem(t.Vertex, o, t.Incoming[o], w)));

                return transaction<script, outpoint, out>(t.Vertex, m);
            }
        };
    
    } // redeem
    
} // abstractions

#endif
