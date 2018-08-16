#ifndef ABSTRACTIONS_REDEEM_STANDARD_HPP
#define ABSTRACTIONS_REDEEM_STANDARD_HPP

#include "mind.hpp"
#include "logos.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template<typename power, typename truth, typename will, typename input_script, typename outpoint>
        struct memory : public association<truth, will, input_script, outpoint> {
            
            
            word<will, input_script, outpoint>& operator()(truth) const {
                return w;
            }
        };
        
        template<typename truth, typename will, typename input_script, typename outpoint>
        theory<truth, will, input_script, outpoint> g(bool (*could)(essence, will, proposition, action), vector<essence>, vector<will>);
        
        template<
            typename input_script,   
            typename outpoint,       
            typename output_script, 
            typename secret>   
        struct standard : public brain<input_script, outpoint, output_script, proposition, accomplishment> {
            using brain = brain<input_script, outpoint, output_script, proposition, accomplishment>;
            using association = association<proposition, accomplishment, input_script, outpoint>;
            using individual = const logos<secret, output_script, proposition, accomplishment, input_script, outpoint> &;
            using multisig = const logos<vector<secret>, output_script, proposition, accomplishment, input_script, outpoint> &;
            
            // conceptually what are we doing to the bitcoin script?
            action none = identity;
            action replace = constant;
            action append = successor;
            
            individual pay_to_address_redeem;
            individual pay_to_address_p2sh_redeem;
            individual pay_to_public_key_redeem;
            individual pay_to_public_key_p2sh_redeem;
            multisig multisig_attach_signature;
            multisig multisig_p2sh_attach_signature;
            
            standard(                     
                individual pay_to_address_redeem,
                individual pay_to_address_p2sh_redeem,
                individual pay_to_public_key_redeem,
                individual pay_to_public_key_p2sh_redeem,
                multisig multisig_attach_signature,
                multisig multisig_p2sh_attach_signature
            ) : brain({replace, append}, ),
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
        };*/
    }
}

#endif
