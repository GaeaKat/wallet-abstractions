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
            vector<index>& Outpoints;
            virtual N Value() const = 0;
            virtual bytestring serialize() const = 0;
            
            vertex(vector<index>& o) : Outpoints(o) {}
        };
        
        template <typename script>
        using prepend = script (*)(script, script);
        
        template <typename script>
        struct output {
            N Value;
            script Pubkey;
            
            output(N v, script p) : Value(v), Pubkey(p) {}
        };
        
        template <typename script, typename outpoint>
        struct word {
            virtual script speak(output<script> prev, vertex<outpoint> tx, uint32_t input_index) const = 0;
        };
        
        template <typename script, typename outpoint>
        using thought = pointer<const word<script, outpoint>>;
        
        template <typename script, typename outpoint>
        struct blockchain {
            pointer<output<script>> operator()(outpoint) const = 0;
        };

        template <
            typename script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename will>           // a desired outcome. 
        class redeemer {
            using thought = thought<script, outpoint>;
            
            const prepend<script> Prepend;
            const blockchain<script, outpoint> Prior;
            
            virtual thought how(script, will) const = 0;
            virtual N value(outpoint o) const = 0;
            
        public:
            redeemer(prepend<script> p, blockchain<script, outpoint>& b) : Prepend(p), Prior(b) {}
            
            script redeem(vertex<outpoint> v, outpoint o, will w, script in) {
                // What is the index of the outpoint we want to redeem?
                uint32_t index = 0;
                for (; index < v.size(); index++) if (v[index] == o) break;
                
                // What's the previous output?
                pointer<output<script>> prevout = Prior(o);
                if (prevout == nullptr) return script();
                
                // Can we really do this? 
                thought hypothetical = how(Prepend(prevout->Pubkey, in), w);
                if (hypothetical == nullptr) return script();
                
                // Speak the magic word! 
                return Prepend(in, hypothetical->speak(*prevout, v, index));
            }
            
            script redeem(vertex<outpoint> v, outpoint o, will w) {
                return redeem(v, o, w, script());
            }
        };
        
        // I don't know what this one should be called. 
        /*template <
            typename script,         // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename will>           // a desired outcome. 
        struct spender : public redeemer<script, outpoint, will> {
            using redeemer = redeemer<script, outpoint, will>;

            N value(outpoint o) const = 0;

            struct transaction{
                vertex<outpoint>& Vertex;
                vector<script> Incoming;

                N amount_transferred() const {
                    int r = 0;
                    for (outpoint o : Incoming)
                    {
                        N v = value(o);
                        if (v == aleph_0) return aleph_0;
                        r += v;
                    }
                    return r;
                }

                bool positive() const {
                    Vertex.Value() >= amount_transferred();
                }
            };

            map<outpoint, script> spend(
                const transaction& t, 
                map<outpoint, script> inputs,
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
        };*/
    
    } // redeem
    
} // abstractions

#endif
