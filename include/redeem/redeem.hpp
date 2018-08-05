#ifndef ABSTRACTIONS_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_HPP

#include<redeem/could.hpp>

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
        typename truth,      // cases that we know how to redeem. 
        typename will>        // a desired outcome. 
    struct concept {
        // Link contains information about how money flows in the
        // blockchain. 
        struct link {
            bool Valid;
            ℕ Value;                 // how much was locked. 
            output_script Function;  // the script that must return true.
            input_script Power;      // how the script shall be made to return true.
            truth Known;         // What is known about this script.  
            
            link() : Valid(false) {}
            link(ℕ v, output_script o, input_script p, truth x)
                : Valid(true), Value(v), Function(o), Power(p), Known(x) {}
        };
        
        struct vertex {
            ℕ Value;
            vector<outpoint> Outpoints;
        };
        
        struct transformation {
            input_script operator()(input_script) const = 0;
        };
        
        using possibility = transformation (* const)(vertex);
        
        possibility* how(truth known, will) const = 0;
        
        link redeem(vertex v, link l, will w) {
            possibility* p = how(l.known, w);
            if (p == nullptr) return link();
            possibility action = *p;
            return Link(l.v, l.script, action(v)(l.Magic), l.known);
        }
        
        struct transaction {
            vertex Vertex;
            map<outpoint, link> Incoming;
            
            ℕ redeemed() {
                int r = 0;
                for (link l : Incoming) r += l.Value;
                return r;
            }
        };
        
        bool positive(transaction t) const {
            t.Vertex.Value >= t.redeemed();
        }
        
        transaction spend(transaction t, will w) const {
            std::vector<link> links = t.Incoming;
            for (link& l : links) {
                l = redeem(t.Vertex, o);
                if (!l.Valid) return {};
            }
            
            return {t.Vertex, links};
        }
        
        // We need this to know what to keep track of earlier on.
        virtual will why(truth known, possibility*) const = 0;
    };

    template<
        typename input_script,
        typename outpoint,
        typename script,
        typename truth,
        typename will>
    struct body : virtual public concept<input_script, outpoint, script, truth, will> {
        
        using design = concept<input_script, outpoint, script, truth, will>;
        using motion = const typename design::possibility*;
        
        const vector<motion>& actions;
        
        body(const vector<motion>& movements) : actions(movements) {}
        
        virtual will why(truth known, motion movement) const override {
            for (motion concrete : actions)
                if (how(known, concrete) == movement)
                    return concrete;
            return nullptr;
        }
    };

    template<
        typename input_script,
        typename outpoint,
        typename script,
        typename truth,
        typename will>
    struct mind : virtual public concept<input_script, outpoint, script, truth, will> {
        
        using design = concept<input_script, outpoint, script, truth, will>;
        using thought = const typename design::possibility*;
        
        vector<ℕ> essences;
        
        virtual thought what_if(ℕ, will, truth) const = 0;
        
        mind() {}
        
        virtual thought how(truth believed, will desire) const override {
            for (int n : essences) 
            {
                thought idea = what_if(n, believed, desire);
                if (idea != nullptr) return idea;
            }
            return nullptr;
        }
    };

    template<
        typename input_script,
        typename outpoint,
        typename script,
        typename truth,
        typename will>
    struct brain :
        virtual public mind<input_script, outpoint, script, truth, will>,
        virtual public body<input_script, outpoint, script, truth, will>
    {
        using design = concept<input_script, outpoint, script, truth, will>;
        using body = body<input_script, outpoint, script, truth, will>;
        using mind = mind<input_script, outpoint, script, truth, will>;
        using thought = const typename design::possibility*;
        
        virtual bool could(ℕ, will, truth, thought) const = 0;
        
        thought what_if(ℕ, will power, truth hypothetical) const {
            for (int nature : mind::essences) 
                for (int deed : body::actions)
                {
                    if(could(nature, power, hypothetical, deed)) return deed;
                }
            return nullptr;
        };
    };
    
    } // redeem
    
} // abstractions

#endif
