#ifndef ABSTRACTIONS_CLAIM_HPP
#define ABSTRACTIONS_CLAIM_HPP

namespace abstractions
{
    
    template <typename quantifier, typename proposition, typename derivation>
    struct claim {
        quantifier Exist;
        proposition SuchThat;
        
        bool verify(derivation d) const {
            if (Exist == quantifier{} || SuchThat == proposition{}) return false;
            
            return Exist(SuchThat, d);
        }
        
        claim(quantifier f, proposition r) : SuchThat(r), Exist(f) {}
        claim() : Exist{}, SuchThat{} {}
    };
    
    template <typename quantifier, typename proposition, typename derivation>
    struct proof : public claim<quantifier, proposition, derivation> {
        
        derivation Derivation;
        
        bool valid() const {
            return verify(Derivation);
        }
        
        proof(quantifier f, proposition r, derivation d) : claim<quantifier, proposition, derivation>{f, r}, Derivation{d} {}
        proof() : claim<quantifier, proposition, derivation>{}, derivation{} {}
    };

}

#endif
