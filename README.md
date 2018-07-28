# hd
contents: 

include/algebra.hpp

This file contains types representing the fundamental cryptographic operations. 

include/hd.hpp

This file contains an abstract class called theory which, if implemented correctly, will generate sequences of hd keys and provide the entire history of the derivation as a data structure. The structure will automatically extend itself when more keys are generated. 

include/bip44.hpp (Not written yet)

This will add a bip44 schema on top of the theory type. 

include/bip32.hpp

Contains information specific to bip 32. 

include/heap.hpp

This is an implementation of theory which should be sufficient for most purposes. 

The library comes with implementations of the theory in trezor-crypto and libbitcoin. 
