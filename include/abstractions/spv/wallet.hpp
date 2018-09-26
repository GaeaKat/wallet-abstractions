#ifndef ABSTRACTIONS_SPV_WALLET_HPP
#define ABSTRACTIONS_SPV_WALLET_HPP

#include "view.hpp"
#include <abstractions/blockchain/merkle.hpp>
#include <abstractions/blockchain/transaction.hpp>
#include <abstractions/blockchain/header.hpp>
#include <abstractions/invalid.hpp>
#include <abstractions/wallet.hpp>
#include <abstractions/observe.hpp>

namespace abstractions  {
    
    namespace block {
        
        template <typename digest, typename header, typename out, typename tx, typename point, typename scr>
        wallet<out> w(
            const headers::merkle_root<header, digest> root,
            const transaction::outputs<tx, out> outs, 
            const transaction::inputs<tx, point, scr> ins,
            const output::script<out, scr> get_script,
            const list<tags<digest, scr>> tag_fns,
            const tree<digest, header> t,
            const merkle::proofs<digest> p,
            const map<digest, tx> txs,
            const memory<digest>& m,
            const digest viewpoint) {
            wallet<out> w;
            return w;
        }
    
    }
    
} 

#endif
