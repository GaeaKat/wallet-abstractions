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
        proof() : Claim{}, derivation{}
    };

}

#endif

