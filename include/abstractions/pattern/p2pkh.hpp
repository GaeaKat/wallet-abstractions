#ifndef ABSTRACTIONS_PATTERN_P2PKH_HPP
#define ABSTRACTIONS_PATTERN_P2PKH_HPP

#include <abstractions/pattern.hpp>

namespace abstractions {
    
    namespace pattern {
        
        template <typename pubkey, typename secret>
        struct p2pkh : public redeemer<pubkey, secret> {
            bool match(script&) const override final;
            
            list<vector<byte>> tags(script&) const override final;
            
            vector<byte> tag(pubkey) const override final;
            
            script make_output(list<pubkey>) const override final;
            
            script make_input(secret) const override final;
            
        };

    }

}

#endif
