#ifndef ABSTRACTIONS_REDEEM_DEFAULT_HPP
#define ABSTRACTIONS_REDEEM_DEFAULT_HPP

#include "mind.hpp"

#include "could.hpp"

namespace abstractions 
{
    namespace redeem
    {        
        template<
            typename input_script,   
            typename outpoint,       
            typename output_script>   
        struct standard : public mind<input_script, outpoint, output_script, ℕ, ℕ> {
            using soul = mind<input_script, outpoint, output_script, ℕ, ℕ>;
            using action = typename soul::thought;
            
            // conceptually what are we doing to the bitcoin script?
            motion none = identity;
            motion replace = constant;
            motion append = successor;
            
            action pay_to_address_redeem;
            action pay_to_address_p2sh_redeem;
            action pay_to_public_key_redeem;
            action pay_to_public_key_p2sh_redeem;
            action multisig_attach_signature;
            action multisig_p2sh_attach_signature;
            
            standard(                     // constructor containing
                action pa, action pah,    // the six basic functions
                action pp, action pph,    // that we actually use. 
                action ma, action mah)
            : soul({replace, append, none}),
                pay_to_address_redeem(pa), 
                pay_to_address_p2sh_redeem(pah), 
                pay_to_public_key_redeem(pp), 
                pay_to_public_key_p2sh_redeem(pph), 
                multisig_attach_signature(ma), 
                multisig_p2sh_attach_signature(mah) {}

            bool could(ℕ form, ℕ outcome, ℕ matter, ℕ impulse) const final override {
                redeem::could(form, outcome, matter, impulse);
            };
            
            action act(ℕ essence, ℕ act) const {
                if (act == none) return nullptr;
                
                if (act == replace)
                    switch (essence) {
                        case pay_to_public_key:
                            return pay_to_public_key_redeem;
                        case pay_to_address: 
                            return pay_to_address_redeem;
                        case public_key_pay_to_script: 
                            return pay_to_public_key_p2sh_redeem;
                        case address_pay_to_script: 
                            return pay_to_address_p2sh_redeem;
                        default: 
                            return nullptr;
                    }
                
                if (act == append)
                    switch (essence) {
                        case pay_to_multisig: 
                            return multisig_attach_signature;
                        case multisig_pay_to_script: 
                            return multisig_p2sh_attach_signature;
                        default: 
                            return nullptr;
                    }
            }
        };
    }
}

#endif
