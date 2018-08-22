#ifndef ABSTRACTIONS_REDEEM_STANDARD_HPP
#define ABSTRACTIONS_REDEEM_STANDARD_HPP

#include "stuff.hpp"

namespace abstractions 
{
    namespace redeem
    {
        template<
            typename input_script,   
            typename outpoint,       
            typename output_script, 
            typename secret, 
            typename address>   
        struct standard : public mind<input_script, outpoint, output_script, accomplishment> {
            using mind = mind<input_script, outpoint, output_script, accomplishment>;
            using brain = brain<input_script, outpoint, accomplishment>;
            using association = association<accomplishment, input_script, outpoint>;
            using individual = individual<secret, output_script, input_script, outpoint> &;
            using multi = multi<secret, output_script, input_script, outpoint> &;
            
            standard(
                sign<secret, input_script, outpoint> add_signature,
                sign<secret, input_script, outpoint> add_signature_and_address, 
            ) : mind(
                {
                    {pay_to_public_key, ppk}, 
                    {pay_to_address, pa}, 
                    {pay_to_multisig, m}, 
                    {public_key_pay_to_script, ppksh}, 
                    {address_pay_to_script, pash}, 
                    {multisig_pay_to_script, msh}
                }) {}
        };
    }
}

#endif
