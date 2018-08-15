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
        template<typename function>
        struct output
        {
            ℕ Value;
                
            function Function; 
                
            output(ℕ v, function o) : Value(v), Function(o) {}
        };
        
        // a vertex represents the flow of bitcoins in the blockchain.
        // We don't need to know about the outputs, so there's just
        // one value that represents all outputs together. There's also
        // a list of links to other locations in the blockchain. 
        template<typename index>
        struct vertex
        {
            virtual ℕ Value() const = 0;
            vector<index> Outpoints;
        };

        template<
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename knowledge,      // cases that we know how to redeem. 
            typename will>           // a desired outcome. 
        struct redeemer : memory<output_script, will> {
            using mine = const posession<output_script, knowledge>&;
            
            // Link contains information about how money flows in the
            // blockchain. 
            struct link
            {
                // Whether this link exists in the database. 
                // agnostic as to whether that means that it exists in the blockchain
                // or if we just don't have the whole blockchain in our database. 
                bool Exists;
                
                mine Posession;
                
                // We need to be able to create the nonexistent value in
                // order to detect limiting cases. 
                link() : Exists(false) {}
                
                // If the necessary information is given, the link 
                // is assumed to exist. You cannot 
                link(mine mine)
                    : Exists(true), Posession(mine) {}
            };
        
            struct possibility {
                virtual input_script operator()(vertex<outpoint>, input_script) const = 0;
            };

            // a thought is a pointer to a possibility. 
            // I think that makes sense. 
            using thought = const possibility*;
            
            virtual thought how(will, knowledge known) const = 0;
            
            bool remember(mine identification, will purpose) const override
            {
                return how(identification.Claim, purpose) != nullptr;
            }
            
            input_script redeem(vertex<outpoint> v, link l, will w, input_script in)
            {
                thought p = how(w, l.Posession.Claim);
                if (p == nullptr) return input_script();
                
                possibility action = *p;
                
                return action(v)(in);
            }
            
            input_script redeem(vertex<outpoint> v, link l, will w) {
                return redeem(v, l, w, input_script());
            }
            
            struct transaction
            {
                vertex<outpoint>& Vertex;
                map<outpoint, link> Incoming;
                
                ℕ amount_transferred() const {
                    int r = 0;
                    for (link l : Incoming()) r += l.Value;
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
