#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include <abstractions/abstractions.hpp>

namespace abstractions 
{
    namespace redeem
    {        
        // a vertex represents the flow of bitcoins in the blockchain.
        // We don't need to know about the outputs, so there's just
        // one value that represents all outputs together. There's also
        // a list of links to other locations in the blockchain. 
        template <typename index>
        struct vertex {
            virtual ℕ Value() const = 0;
            vector<index> Outpoints;
        };
        
        template <typename script>
        using prepend = script (*)(script, script);
        
        template <typename script, typename outpoint>
        struct word {
            virtual script speak(vertex<outpoint>) const = 0;
        };
        
        template <typename script, typename outpoint>
        using thought = pointer<const word<script, outpoint>>;
        
        template <typename script, typename outpoint>
        struct blockchain {
            pointer<script> operator()(outpoint) const = 0;
        };

        template <
            typename script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename will>           // a desired outcome. 
        class redeemer {
            using thought = thought<script, outpoint>;
            
            const prepend<script> Prepend;
            const blockchain<script, outpoint> Prior;
            
            virtual thought what(script, will) const = 0;
            
        public:
            redeemer(prepend<script> p, blockchain<script, outpoint>& b) : Prepend(p), Prior(b) {}
            
            script redeem(vertex<outpoint> v, outpoint o, will w, script in) {
                pointer<script> output = Prior(o);
                if (output == nullptr) return script();
                
                thought logos = what(Prepend(*output, in), w);
                if (logos == nullptr) return script();
                
                return p(in, logos->speak(v));
            }
            
            script redeem(vertex<outpoint> v, outpoint o, will w) {
                return redeem(v, o, w, script());
            }
        };
        
        // I don't know what this one should be called. 
        template <
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename will>           // a desired outcome. 
        struct spender : public redeemer<script, outpoint, will> {
            using redeemer = redeemer<script, outpoint, will>;

            ℕ value(outpoint o) const = 0;

            struct transaction{
                vertex<outpoint>& Vertex;
                vector<outpoint> Incoming;

                ℕ amount_transferred() const {
                    int r = 0;
                    for (outpoint o : Incoming)
                    {
                        ℕ v = value(o);
                        if (v == ℵ0) return ℵ0;
                        r += v;
                    }
                    return r;
                }

                bool positive() const {
                    Vertex.Value() >= amount_transferred();
                }
            };

            map<outpoint, input_script> spend(
                const transaction& t, 
                map<outpoint, input_script> inputs,
                will w) const
            {
                std::map<outpoint, script> m;
                for (outpoint o : t.Incoming) {
                    script i = redeemer::redeem(t.Vertex(), t.Incoming[o], w, inputs[o]);
                    if (i == script()) return {};
                    m[o] = i;
                }

                return m;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
