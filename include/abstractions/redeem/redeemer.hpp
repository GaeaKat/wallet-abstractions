#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include <abstractions/redeem/memory.hpp>

namespace abstractions 
{
    namespace redeem
    {
        // An output is a disconnected piece of a bitcoin transaction, 
        // containing a natural number value and function by which
        // that value is redeemed by this output, if it were to exist
        // in the blockchain. 
        template <typename function>
        struct output
        {
            ℕ Value;
                
            function Script; 
                
            output(ℕ v, function o) : Value(v), Script(o) {}
        };
        
        // a vertex represents the flow of bitcoins in the blockchain.
        // We don't need to know about the outputs, so there's just
        // one value that represents all outputs together. There's also
        // a list of links to other locations in the blockchain. 
        template <typename index>
        struct vertex
        {
            virtual ℕ Value() const = 0;
            vector<index> Outpoints;
        };
        
        template <typename input_script, typename outpoint>
        struct possibility {
            virtual input_script operator()(vertex<outpoint>, input_script) const = 0;
        };

        // a thought is a pointer to a possibility. 
        // I think that makes sense.
        template <typename input_script, typename outpoint>
        using thought = const possibility<input_script, outpoint>*;
        
        template<typename function, typename knowledge>
        struct posession {
            output<function> Output;
                
            // truth claims concerning this output. 
            // (such as what information we have about it.) 
            // Also may contain an index as to how tho find that 
            // information. 
            knowledge Claim; 
            
            virtual bool valid() const = 0;
        protected:
            posession(ℕ v, function script, knowledge claim) : output<function>(v, script), Claim(claim) {}
        };
        
        template <typename input_script, typename outpoint, typename output_script, typename knowledge, typename will>
        using how = thought<input_script, outpoint> (*)(posession<output_script, knowledge>, will);

        template <
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename knowledge,      // cases that we know how to redeem. 
            typename will>           // a desired outcome. 
        struct redeemer : memory<output_script, will> {
            using mine = const posession<output_script, knowledge>&;
            using thought = thought<input_script, outpoint>;
            using possibility = possibility<input_script, outpoint>;
            
            const how<input_script, outpoint, output_script, knowledge, will> h;
            
            bool remember(mine identification, will purpose) const override
            {
                return h(identification.Claim, purpose) != nullptr;
            }
            
            input_script redeem(vertex<outpoint> v, mine l, will w, input_script in)
            {
                thought p = h(w, l.Claim);
                if (p == nullptr) return input_script();
                
                possibility action = *p;
                
                return action(v)(in);
            }
            
            input_script redeem(vertex<outpoint> v, mine l, will w) {
                return redeem(v, l, w, input_script());
            }
            
            struct transaction
            {
                vertex<outpoint>& Vertex;
                map<outpoint, mine> Incoming;
                
                ℕ amount_transferred() const {
                    int r = 0;
                    for (mine l : Incoming) r += l.Output.Value;
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
                    input_script i = redeem(t.Vertex(), t.Incoming[o], w, inputs[o]);
                    if (i == input_script()) return {};
                    m[o] = i;
                }
                
                return m;
            }
        };
    
    } // redeem
    
} // abstractions

#endif
