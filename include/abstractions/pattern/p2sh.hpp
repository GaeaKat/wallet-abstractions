#ifndef ABSTRACTIONS_PATTERN_P2SH_HPP
#define ABSTRACTIONS_PATTERN_P2SH_HPP

#include <abstractions/pattern.hpp>

namespace abstractions {
    
    namespace pattern {
        
        template <typename pubkey, typename secret>
        class p2sh : public redeemer<pubkey, secret> {
            redeemer<pubkey, secret>& inner;
        public:
            
            bool match(script&) const override final;
            
            list<vector<byte>> tags(script&) const override final;
            
            slice<byte> tag(pubkey) const override final;
            
            script make_output(list<pubkey>) const override final;
            
            script make_input(secret) const override final;
            
        };

    }

}

#endif
