#ifndef ABSTRACTIONS_REDEEM_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_REDEEM_HPP

#include<abstractions.hpp>

namespace abstractions 
{
    // redeem contains a high-level way of redeeming bitcoin txs.
    namespace redeem
    {

    template<
        typename output,         // 
        typename knowledge,      // cases that we know how to redeem. 
        typename will>           // a desired outcome. 
    struct memory {
        // my_output represents an output that we own and information
        // about how we own it. In other words, stuff like do we
        // have all necessary keys? Do we have some keys but not all?
        struct posession {
            output Output;
            
            // truth claims concerning this output. 
            // (such as what information we have about it.) 
            // Also may contain an index as to how tho find that 
            // information. The sky's the limit. 
            knowledge Claim; 
            
            posession(output o, knowledge c) : Output(o), Claim(c) {}
        };
        
        // should we remember this observation given this known information about it for the given purpose?
        virtual bool remember(posession identification, will purpose) const = 0;
    };
        
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

    template<
        typename input_script,   // means of redemption. 
        typename outpoint,       // way if indexing a previous output. 
        typename output_script,  // an amount of funds locked behind a puzzle. 
        typename knowledge,      // cases that we know how to redeem. 
        typename will>           // a desired outcome. 
    struct redeemer : public memory<output<input_script>, knowledge, will> {
        using sin = memory<output<input_script>, knowledge, will>;
        using mine = typename sin::posession;
        
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
        
        struct vertex {
            ℕ Value;
            vector<outpoint> Outpoints;
        };
        
        using transformation = input_script (* const)(input_script);
        
        using possibility = transformation (* const)(vertex);
        
        // a thought is a pointer to a possibility. 
        // I think that makes sense. 
        using thought = const possibility*;
        
        thought how(will, knowledge known) const = 0;
        
        bool remember(mine identification, will purpose) const override {
            return how(identification.Claim, purpose) != nullptr;
        }
        
        link redeem(vertex v, link l, will w) {
            mine r = l.Posession;
            thought p = how(w, r.Claim);
            if (p == nullptr) return link();
            possibility action = *p;
            return Link(l.v, l.script, action(v)(l.Magic), l.known);
        }
        
        struct transaction {
            vertex Vertex;
            map<outpoint, link> Incoming;
            
            ℕ amount_transferred() const {
                int r = 0;
                for (link l : Incoming) r += l.Value;
                return r;
            }
            
            bool positive() const {
                Vertex.Value >= amount_transferred();
            }
        };
        
        transaction spend(transaction t, will w) const {
            std::vector<link> links = t.Incoming;
            for (link& l : links) {
                l = redeem(t.Vertex, w);
                if (!l.Valid) return {};
            }
            
            return {t.Vertex, links};
        }
    };
    
    template<typename truth>
    struct knowledge {
        ℕ Category;
        truth Observed;
    };
    
    template<
        typename input_script,   // means of redemption. 
        typename outpoint,       // way if indexing a previous output. 
        typename output_script,  // an amount of funds locked behind a puzzle. 
        typename truth,          // cases that we know how to redeem. 
        typename will>           // a desired outcome. 
    struct mind : public redeemer<input_script, outpoint, output_script, knowledge<truth>, will> {
        using logos = redeemer<input_script, outpoint, output_script, knowledge<truth>, will>;
        using action = typename logos::thought;
            
        vector<ℕ> moves;
            
        mind(vector<ℕ> m) : moves(m) {}
            
        virtual action act(ℕ essence, ℕ act) const = 0;
        
        virtual bool could(ℕ form, will outcome, truth matter, ℕ motion) const = 0;

        action how(will outcome, truth known) const final override {
            for (ℕ move : moves) 
                if (could(known.Category, outcome, known.Observed, move)) 
                    return act(known.Category, move);
            return nullptr;
        }
    };
    
    } // redeem
    
} // abstractions

#endif
