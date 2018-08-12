#ifndef ABSTRACTIONS_REDEEM_REDEEMER_HPP
#define ABSTRACTIONS_REDEEM_REDEEMER_HPP

#include<redeem/memory.hpp>

namespace abstractions 
{
    namespace redeem
    {
        // An output is a disconnected piece of a bitcoin transaction, 
        // containing a natural number value and function by which
        // that value is redeemed by this output, if it were to exist
        // in the blockchain. 
        template<typename function>
        struct output {
            ℕ Value;
                
            function Function; 
                
            output(ℕ v, function o) : Value(v), Function(o) {}
        };
        
        // a transformation changes one power into another. 
        template<typename power>
        struct transformation {
            power operator()(power) const = 0;
        }
        
        // a vertex represents the flow of bitcoins in the blockchain.
        // We don't need to know about the outputs, so there's just
        // one value that represents all outputs together. There's also
        // a list of links to other locations in the blockchain. 
        template<typename index>
        struct vertex {
            ℕ Value;
            vector<index> Outpoints;
        };
        
        template<typename power, typename index>
        using possibility = transformation<power> (* const)(vertex<index>);

        // a thought is a pointer to a possibility. 
        // I think that makes sense. 
        template<typename power, typename index>
        using thought = const possibility<power, index>*;

        template<
            typename input_script,   // means of redemption. 
            typename outpoint,       // way if indexing a previous output. 
            typename output_script,  // an amount of funds locked behind a puzzle. 
            typename knowledge,      // cases that we know how to redeem. 
            typename will>           // a desired outcome. 
        struct redeemer : public memory<output<input_script>, knowledge, will> {
            using sin = memory<output<input_script>, knowledge, will>;
            using mine = typename sin::posession;
            
            using thought = thought<input_script, outpoint>;
            using possibility = possibility<input_script, outpoint>;
            
            // Link contains information about how money flows in the
            // blockchain. 
            struct link {
                // Whether this link exists in the database. 
                // agnostic as to whether that means that it exists in the blockchain
                // or if we just don't have the whole blockchain in our database. 
                bool Exists;
                
                mine Posession;             
                
                // How the script shall be made to return true. 
                // In other words, the input script. 
                input_script Power;
                
                // We need to be able to create the nonexistent value in
                // order to detect limiting cases. 
                link() : Exists(false) {}
                
                // If the necessary information is given, the link 
                // is assumed to exist. You cannot 
                link(mine mine, input_script word)
                    : Exists(true), Posession(mine), Power(word) {}
            };
            
            thought how(will, knowledge known) const = 0;
            
            bool remember(mine identification, will purpose) const override {
                return how(identification.Claim, purpose) != nullptr;
            }
            
            link redeem(vertex<outpoint> v, link l, will w) {
                thought p = how(w, l.Posession.Claim);
                if (p == nullptr) return link();
                
                possibility action = *p;
                
                return Link(l.v, l.script, action(v)(l.Magic), l.known);
            }
            
            struct transaction {
                virtual vertex<outpoint> Vertex() const = 0;
                virtual map<outpoint, link> Incoming() const = 0;
                
                ℕ amount_transferred() const {
                    int r = 0;
                    for (link l : Incoming()) r += l.Value;
                    return r;
                }
                
                bool positive() const {
                    Vertex().Value >= amount_transferred();
                }
            };
            
            transaction spend(const transaction& t, will w) const {
                std::vector<link> links = t.Incoming;
                for (link& l : links) {
                    l = redeem(t.Vertex(), w);
                    if (!l.Valid) return {};
                }
                
                return {t.Vertex(), links};
            }
        };
    
    } // redeem
    
} // abstractions

#endif
