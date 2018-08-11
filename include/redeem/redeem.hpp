#ifndef ABSTRACTIONS_REDEEM_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_REDEEM_HPP

#include<abstractions.hpp>

namespace abstractions 
{
    // redeem contains a high-level way of redeeming bitcoin txs.
    namespace redeem
    {

    template<
        typename input_script,   // means of redemption. 
        typename outpoint,       // way if indexing a previous output. 
        typename output_script,  // an amount of funds locked behind a puzzle. 
        typename truth,          // cases that we know how to redeem. 
        typename will>           // a desired outcome. 
    struct redeemer {
        // An output is a disconnected piece of a bitcoin transaction, 
        // containing a natural number value and function by which
        // that value is redeemed by this output, if it were to exist
        // in the blockchain. 
        struct output {
            ℕ Value;
            
            output_script Function;  
            
            output(ℕ v, output_script o) : Value(v), Function(o) {}
        };
        
        // relation_to_owner represents an output that we own and information
        // about how we own it. In other words, stuff like do we
        // have all necessary keys? Do we have some keys but not all?
        struct relation_to_owner {
            const output Output;
            
            // Some category that this output fits in. 
            ℕ Essence;
            
            // truth claims concerning this output. 
            // (such as what information we have about it.) 
            // Also may contain an index as to how tho find that 
            // information. The sky's the limit. 
            truth Claim; 
            
            relation_to_owner(output o, truth c) : Output(o), Claim(c) {}
        };
        
        // Link contains information about how money flows in the
        // blockchain. 
        struct link {
            // Whether this link exists in the database. 
            // agnostic as to whether that means that it exists in the blockchain
            // or if we just don't have the whole blockchain in our database. 
            bool Exists;
            
            relation_to_owner Posession;             
            
            // How the script shall be made to return true. 
            // In other words, the input script. 
            input_script Power;
            
            // We need to be able to create the nonexistent value in
            // order to detect limiting cases. 
            link() : Exists(false) {}
            
            // If the necessary information is given, the link 
            // is assumed to exist. You cannot 
            link(relation_to_owner mine, input_script word)
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
        
        thought how(ℕ essence, will, truth known) const = 0;
        
        link redeem(vertex v, link l, will w) {
            relation_to_owner r = l.Posession;
            thought p = how(r.Essence, w, r.Claim);
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
        
        // should we remember this observation given this known information about it for the given purpose?
        bool remember(relation_to_owner identification, will purpose) const {
            return how(identification.Essence, identification.Claim, purpose) != nullptr;
        }
    }; 
    
    template<
        typename input_script,   // means of redemption. 
        typename outpoint,       // way if indexing a previous output. 
        typename output_script,  // an amount of funds locked behind a puzzle. 
        typename truth,          // cases that we know how to redeem. 
        typename will>           // a desired outcome. 
    struct body : public redeemer<input_script, outpoint, output_script, truth, will> {
        using logos = redeemer<input_script, outpoint, output_script, truth, will>;
        using action = typename logos::thought;
            
        vector<ℕ> moves;
            
        body(vector<ℕ> m) : moves(m) {}
            
        action act(ℕ essence, ℕ act) const = 0;

        action how(ℕ essence, will outcome, truth known) const final override {
            for (ℕ move : moves) 
                if (could(essence, outcome, known, move)) 
                    return act(essence, move);
            return nullptr;
        }
    };
    
    } // redeem
    
} // abstractions

#endif
