#ifndef ABSTRACTIONS_COLORED_HPBOC_HPP
#define ABSTRACTIONS_COLORED_HPBOC_HPP

#include <abstractions/colored/colored.hpp>
#include <abstractions/encoding/ascii.hpp>
#include <abstractions/encoding/utf8.hpp>
#include <abstractions/blockchain/transaction.hpp>

namespace abstractions
{

    namespace colored
    {
        
        namespace slp {
            
            // get metadata for a tx of a given color. 
            template <typename tx, typename point, typename C>
            meta<point, C> interpret(tx, C);
            
            // Some new types. 
            using script = vector<byte>;
            
            using quantity = uint64_t;
            
            using hash = const std::array<byte, 32>;
            
            using color = hash;
            
            // Several types of tokens have been named, but only the first
            // has been defined. The others are reserved but meaningless
            // and unsupported for now. 
            enum token_type {
                none = 0, 
                permissionless = 1, // Permissionless Token Type
                security = 2,       // Reserved for Security Token Type (see Appendix A)
                voting = 3,         // Reserved for Voting Token Type
                ticketing = 4,      // Reserved for Ticketing Token Type
            };
            
            namespace scripts {
                
                struct genesis {
                    token_type Token;
                    unicode Ticker;
                    unicode Name;
                    unicode DocumentUrl;
                    hash* DocumentHash;
                    byte Decimals;
                    byte* MintBatonVout;
                    quantity InitialTokenMintQuantity;
                    
                    bool valid();
                        
                    script write();
                    
                    genesis() : Token(none), Ticker{}, Name{}, DocumentUrl{}, DocumentHash(nullptr), Decimals(0), MintBatonVout(nullptr), InitialTokenMintQuantity(0) {}
                    genesis(token_type t, unicode x, unicode n, unicode u, hash* h, byte d, byte* m, quantity q)
                        : Token(t), Ticker(x), Name(n), DocumentUrl(u), DocumentHash(h), Decimals(d), MintBatonVout(m), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, unicode u, hash* h, byte d, quantity q)
                        : Token(t), Ticker(x), Name(n), DocumentUrl(u), DocumentHash(h), Decimals(d), MintBatonVout(nullptr), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, byte d, byte* m, quantity q)
                        : Token(t), Ticker(x), Name(n), DocumentUrl(""), DocumentHash(nullptr), Decimals(d), MintBatonVout(m), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, byte d, quantity q)
                        : Token(t), Ticker(x), Name(n), DocumentUrl(""), DocumentHash(nullptr), Decimals(d), MintBatonVout(nullptr), InitialTokenMintQuantity(q) {}
                    
                    static const genesis read(script);
                };
                    
                struct mint {
                    token_type Token;
                    color Color; 
                    byte* MintBatonVout;
                    quantity AdditionalTokenQuantity;
                    
                    bool valid();
                        
                    script write();
                    
                    mint() : Token(none), Color(), MintBatonVout(nullptr), AdditionalTokenQuantity(0) {};
                    
                    static const mint read(script);
                };
                    
                struct send {
                    token_type Token;
                    color Color; 
                    vector<quantity> OutputQuantities;
                    
                    script write();
                    
                    bool valid();
                    
                    send(): Token(none), Color(), OutputQuantities(0) {};
                    
                    static const send read(script);
                };
            
            }
            
            namespace type_1 {
                
                script genesis(
                    unicode ticker,
                    unicode name,
                    encoding::ascii::string document_url,
                    hash* document_hash,
                    byte decimals, 
                    byte* mint_baton_vout,
                    quantity initial_token_mint_quantity);
                
                script mint(
                    color id, 
                    byte* mint_baton_vout,
                    quantity additional_token_quantity);
                
                script send(
                    color id, 
                    vector<quantity> output_quantities);
                
            }
            
        }
    
    }

}

#endif
