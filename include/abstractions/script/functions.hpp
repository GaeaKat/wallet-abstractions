// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef ABSTRACTIONS_SCRIPT_FUNCTIONS
#define ABSTRACTIONS_SCRIPT_FUNCTIONS

#include "script.hpp"
#include <abstractions/wallet/address.hpp>
#include <abstractions/wallet/keys.hpp>
#include <data/io/unimplemented.hpp>

namespace abstractions::script {
    pointer<program> op(program::op);
    pointer<program> sequence(vector<pointer<program>>);
    pointer<program> push_data(const bytes&);
    pointer<program> push_data(hex);
    pointer<program> push(const bitcoin::signature&);
    pointer<program> push(const bitcoin::pubkey&);
    pointer<program> push(const secp256k1::uncompressed_pubkey&);
    pointer<program> push(const secp256k1::compressed_pubkey&);
    pointer<program> push(const bitcoin::address&);
    pointer<program> push(const sha256::digest&);
    pointer<program> push(int64);
    pointer<program> push(uint64);
    pointer<program> push(uint32);
    pointer<program> noop();
    pointer<program> repeat(pointer<program>, uint32);
    pointer<program> dup();
    pointer<program> swap();
    pointer<program> to_alt();
    pointer<program> from_alt();
    pointer<program> cat(uint32);
    pointer<program> concat(uint32);
    pointer<program> rotate_bytes_left(uint32);
    pointer<program> split(uint32);
    pointer<program> equal();
    pointer<program> verify();
    pointer<program> equal_verify();
    pointer<program> bitcoin_hash();
    pointer<program> address_hash();
    pointer<program> sha256_hash();
    pointer<program> check_signature(); 
    
    inline pointer<program> op(program::op o) {
        return std::make_shared<program::op_code>(o);
    }
    
    inline pointer<program> sequence(vector<pointer<program>> v) {
        return std::make_shared<program::sequence>(v);
    }
    
    inline pointer<program> push_data(bytes& b) {
        return std::make_shared<program::push>(b);
    }
    
    inline pointer<program> push_data(hex h) {
        return push_data((bytes)(h));
    }
    
    inline pointer<program> push(const bitcoin::signature&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(const bitcoin::pubkey&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(const secp256k1::uncompressed_pubkey&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(const secp256k1::compressed_pubkey&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(const bitcoin::address&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(const sha256::digest&) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(int64) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(uint64) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> push(uint32) {
        throw data::method::unimplemented{};
    }
    
    inline pointer<program> repeat(pointer<program> p, uint32 n) {
        return std::make_shared<program::repeated>(n, p);
    }
    
    inline pointer<program> dup() {
        return op(program::OP_DUP);
    }
    
    inline pointer<program> to_alt() {
        return op(program::OP_TOALTSTACK);
    }
    
    inline pointer<program> from_alt() {
        return op(program::OP_FROMALTSTACK);
    }
    
    inline pointer<program> cat() {
        return op(program::OP_CAT);
    }
    
    inline pointer<program> concat(uint32 n) {
        return repeat(cat(), n - 1);
    }
    
    inline pointer<program> rotate_bytes_left(uint32 n) {
        return sequence({split(n), cat()});
    }
    
    inline pointer<program> split(uint32 n) {
        return sequence({push(n), op(program::OP_SPLIT)});
    }
    
    inline pointer<program> equal() {
        return op(program::OP_EQUAL);
    }
    
    inline pointer<program> verify() {
        return op(program::OP_VERIFY);
    }
    
    inline pointer<program> equal_verify() {
        return op(program::OP_EQUALVERIFY);
    }
    
    inline pointer<program> bitcoin_hash() {
        return op(program::OP_HASH256);
    }
    
    inline pointer<program> address_hash() {
        return op(program::OP_HASH160);
    }
    
    inline pointer<program> check_signature() {
        return op(program::OP_CHECKSIG);
    }
    
}

#endif

