#ifndef ABSTRACTIONS_REDEEM_STANDARD_HPP
#define ABSTRACTIONS_REDEEM_STANDARD_HPP

#include "rights.hpp"

namespace abstractions 
{
    namespace redeem
    {        
        template <typename secret, typename script, typename outpoint>
        struct right_pay_to_address : public single<secret, script, outpoint, bytestring, accomplishment> {
            right_pay_to_address(sign<secret, script, outpoint> add_signature_and_pubkey) : {}
        };
        
        template <typename secret, typename script, typename outpoint>
        struct right_pay_to_pubkey : public single<secret, script, outpoint, bytestring, accomplishment> {
            right_pay_to_pubkey(sign<secret, script, outpoint> add_signature) : {}
        };
        
        template <typename secret, typename script, typename outpoint>
        struct right_script_pay_to_address : public single<secret, script, outpoint, bytestring, accomplishment> {
            right_script_pay_to_address(sign<secret, script, outpoint> add_signature_and_pubkey) : {}
        };
        
        template <typename secret, typename script, typename outpoint>
        struct right_script_pay_to_pubkey : public single<secret, script, outpoint, bytestring, accomplishment> {
            right_script_pay_to_pubkey(sign<secret, script, outpoint> add_signature) : {}
        };
        
        template <typename secret, typename script, typename outpoint>
        struct right_multisig : public multiple<secret, script, outpoint, bytestring, accomplishment> {
            right_multisig(sign<secret, script, outpoint> add_signature) : {}
        };
        
        template <typename secret, typename script, typename outpoint>
        struct right_script_multisig : public multiple<secret, script, outpoint, bytestring, accomplishment> {
            right_script_multisig(sign<secret, script, outpoint> add_signature) : {}
        };

        template<
            typename script,   
            typename outpoint,
            typename secret>   
        struct standard : public mind<script, outpoint, bytestring, accomplishment> {
            using mind = mind<script, outpoint, bytestring, accomplishment>;
            
            standard(
                sign<secret, script, outpoint> add_signature,
                sign<secret, script, outpoint> add_signature_and_pubkey, 
            ) : mind(
                {
                    {pay_to_public_key, ppk}, 
                    {pay_to_address, pa}, 
                    {pay_to_multisig, m}, 
                    {public_key_pay_to_script, ppksh}, 
                    {address_pay_to_script, pash}, 
                    {multisig_pay_to_script, msh}
                }, db) {}
        };
    }
}

#endif
