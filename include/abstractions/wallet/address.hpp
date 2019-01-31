#ifndef ABSTRACTIONS_WALLET_ADDRESS_HPP
#define ABSTRACTIONS_WALLET_ADDRESS_HPP

#include <data/crypto/sha256.hpp>
#include <data/crypto/secp256k1.hpp>
#include <abstractions/fundamental.hpp>

namespace abstractions {
    
    struct address : ::data::sha256::digest {
        char Prefix;
            
        string write();
        
        static address read(string& s);
        
        address(data::secp256k1::pubkey);
        address(data::secp256k1::secret);
        
    private:
        address(char prefix, ::data::sha256::digest d) : ::data::sha256::digest(d), Prefix{prefix} {}
    };
    
    namespace cashaddr {
        
        address read(string& s);
        
        string write(address& a);
        
    }
    
} 

#endif
