#ifndef ABSTRACTIONS_CLAIM_HPP
#define ABSTRACTIONS_CLAIM_HPP

namespace abstractions
{
    
    template <typename quantifier, typename proposition, typename derivation>
    struct claim {
        quantifier Exists;
        proposition SuchThat;
        
        bool verify(derivation d) const {
            if (Exists == quantifier{} || SuchThat == proposition{}) return false;
            
            return Exists(SuchThat, d);
        }
        
        claim(quantifier f, proposition r) : SuchThat(r), Exists(f) {}
        claim() : Exists{}, SuchThat{} {}
    };
    
    template <typename quantifier, typename proposition, typename derivation>
    struct proof {
        claim<quantifier, proposition, derivation> Claim;
        
        derivation Derivation;
        
        bool valid() const {
            return verify(Derivation);
        }
        
        proof(quantifier f, proposition r, derivation d) : Claim{f, r}, Derivation{d} {}
        proof() : Claim{}, derivation{} {}
    };
    
    template <typename f, typename key, typename value>
    struct check_inverse {
        f Function;
        
        bool operator()(value v, key k) {
            return v == Function(k);
        }
        
    };
    
    template <typename f, typename key, typename value>
    claim<check_inverse<f, key, value>, value, key> claim_inverse(f fun, value v) {
        return claim<check_inverse<f, key, value>, value, key>{check_inverse<f, key, value>{fun}, v};
    }
    
    template <typename f, typename key, typename value>
    proof<check_inverse<f, key, value>, value, key> prove_inverse(f fun, value v, key k) {
        return proof<check_inverse<f, key, value>, value, key>{claim_inverse(fun, v), k};
    }
    
    template <typename to_public, typename secret, typename pubkey>
    struct keypair {
        pubkey Pubkey;
        secret Secret;
    };

}

#endif

