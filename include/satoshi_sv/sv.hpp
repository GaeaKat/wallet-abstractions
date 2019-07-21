// Copyright (c) 2018-2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef SATOSHI_SV_SV
#define SATOSHI_SV_SV

#include <abstractions/crypto/hash/sha256.hpp>
#include <abstractions/wallet/transaction.hpp>

#include <satoshi_sv/src/uint256.h>
#include <satoshi_sv/src/script/interpreter.h>

namespace abstractions::sv {
    
    using namespace ::sv;
    
    using digest = sv::uint256;
    
    sha256::digest convert(const digest);
    
    CTransaction convert(const bitcoin::transaction&);
    CScript convert(bitcoin::script&);
} 

#endif

