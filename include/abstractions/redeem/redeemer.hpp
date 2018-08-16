#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include <abstractions/abstractions.hpp>
#include "could.hpp"

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
        
        template <typename input_script, typename outpoint>
        struct word {
            virtual input_script speak(vertex<outpoint>, input_script) const = 0;
        };

        template <
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename will>           // a desired outcome. 
        struct redeemer {
            using word = word<input_script, outpoint>;
            
            input_script redeem(vertex<outpoint> v, outpoint o, will w, input_script in)
            {
                word const* logos = how(o, w);
                if (logos == nullptr) return input_script();                
                return logos->speak(v, in);
            }
            
            input_script redeem(vertex<outpoint> v, outpoint o, will w) {
                return redeem(v, o, w, input_script());
            }
            
        private: 
            virtual word const* how(outpoint, will) const = 0;
        };
        
        // I don't know what this one should be called. 
        template <
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename will>           // a desired outcome. 
        struct spender : redeemer<input_script, outpoint, output_script, will> {
            using redeemer = redeemer<input_script, outpoint, output_script, will>;

            ℕ value(outpoint o) const = 0;

            struct transaction
            {
                
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
                std::map<outpoint, input_script> m;
                for (outpoint o : t.Incoming) {
                    input_script i = redeemer::redeem(t.Vertex(), t.Incoming[o], w, inputs[o]);
                    if (i == input_script()) return {};
                    m[o] = i;
                }

                return m;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
