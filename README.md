# Wallet Abstractions

Ideas about wallets and transactions. 

contents: 

include/algebra.hpp

Types representing the fundamental cryptographic operations. 

include/derivation.hpp

Types representing sequences of operations. 

include/hd.hpp

Abstract class called theory which will potentially generate
sequences of keys given a derivation. 

include/heap.hpp

This is an implementation of theory which should be sufficient for most purposes. 

It is possible to extract all keys in a sequence so as to perform computations on them.

include/bip32.hpp

Contains information specific to bip 32. 

include/bip44.hpp 

bip44 schema on top of the theory type. 

The library comes with implementations of the cryptographic keys in trezor-crypto and libbitcoin. 
