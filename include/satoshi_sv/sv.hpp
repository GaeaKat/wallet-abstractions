// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_SV
#define SATOSHI_SV_SV

#include <abstractions/crypto/hash/sha256.hpp>
#include <uint256.h>
#include <script/interpreter.h>

namespace abstractions::sv {
    
    using digest = ::uint256;
    
    sha256::digest convert(const digest);
    
    CTransaction read_transaction(bytes_view);
    CScript read_script(bytes_view);
} 

#endif

