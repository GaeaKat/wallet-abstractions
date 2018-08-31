#ifndef ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP
#define ABSTRACTIONS_REDEEM_LIBBITCOIN_BASIC_HPP

#include "words.hpp"

namespace abstractions 
{
    
    namespace redeem
    {
        N libbitcoin_output_value(output);
        
        script libbitcoin_output_script(output);
        
        script libbitcoin_prepend_script(script, script);
        
        const mind<script, outpoint, output, hash, accomplishment> libbitcoin_basic_redeemer(
            blockchain<script, outpoint>& bcx,
            const database<key<ec_secret, ec_compressed>, hash>& d
        ) {
            return mind<script, outpoint, output, hash, accomplishment>(
                {libbitcoin_pay_to_public_key_hash(d)}, 
                libbitcoin_output_value,
                libbitcoin_output_script, 
                libbitcoin_prepend_script, bcx);
        }
        
    }
    
}

#endif
