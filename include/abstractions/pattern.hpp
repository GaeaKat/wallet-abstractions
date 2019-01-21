#ifndef ABSTRACTIONS_PATTERN_HPP
#define ABSTRACTIONS_PATTERN_HPP

#include <abstractions/data.hpp>
#include <abstractions/fundamental.hpp>
#include <abstractions/key.hpp>
#include <abstractions/bitcoin/outpoint.hpp>

namespace abstractions {
    
    namespace pattern {
        
        using script = vector<byte>;
        
        template <typename pubkey>
        struct pattern {
            // whether a script matches a given pattern. 
            virtual bool match(script&) const = 0;
            
            // The tags found in a given output which can be used to identify
            // the script as belonging to us. 
            virtual list<vector<byte>> tags(script&) const = 0;
            
            // The tag corresponding to a given pubkey. 
            virtual vector<byte> tag(pubkey) const = 0;
            
            // create an output with the given pubkey. 
            virtual script make_output(list<pubkey>) const = 0;
            
            bool redeemable(script& s, list<pubkey>) const final;
        };
        
        template <typename pubkey, typename secret>
        struct redeemer : public pattern<pubkey> {
            virtual script make_input(secret) const = 0;
        };

    }
    
    template <typename digest, typename priv, typename pub>
    struct spendable {
        bitcoin::outpoint<digest> Outpoint;
        key::pair<priv, pub> Keypair;
        pattern::redeemer<pub, priv> Redeemer; 
        
        pattern::script redeem() const {
            return Redeemer.make_input(Keypair.Secret);
        }
        
        spendable(bitcoin::outpoint<digest> o, key::pair<priv, pub> k, pattern::redeemer<pub, priv> r) : Outpoint{o}, Keypair{k}, Redeemer{r} {}
    };
    
    template <typename truth, typename pat, typename key>
    pat* observe(list<pat*> theory, pattern::script out, key k) {        
        for (pat* p : theory) if (p->redeemable(out, k)) return p;
        return nullptr;
    } 
    
} 

#endif

