#ifndef ABSTRACTIONS_WALLET_ADDRESS_HPP
#define ABSTRACTIONS_WALLET_ADDRESS_HPP

#include <data/crypto/sha256.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    struct address : ::data::sha256::digest {
        char Prefix;
            
        string write();
        
        static address read(string& s);
        
    private:
        address(char prefix, ::data::sha256::digest d) : ::data::sha256::digest(d), Prefix{prefix} {}
    };
    
    namespace cashaddr {
        
        address read(string& s);
        
        string write(address& a);
        
    }
    
} 

#endif
