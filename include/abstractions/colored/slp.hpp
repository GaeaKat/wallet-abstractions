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
            
            // Some constants which will be important. 
            const byte op_return = 0x6a;
            
            const byte min_push = 0x01;
            const byte max_push = 0x4b;
            
            // A thing that has to go in every script. 
            const uint32_t lokad = 0x534c5000;
            
            const byte push_data1 = 0x4c;
            const byte push_data2 = 0x4d;
            const byte push_data4 = 0x4e;
            
            const string genesis_string = "GENESIS";
            const string mint_string = "MINT";
            const string send_string = "SEND";
            
            const N max_outputs = 19;
            
            namespace type_1 {
                
                script genesis(
                    unicode ticker,
                    unicode name,
                    unicode document_url,
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
            
            namespace low {
                
                // only token type 1 is currently defined. 
                inline bool valid_token_type(token_type t) {
                    return t == permissionless;
                }
                
                inline bool valid_color(color h) {
                    return h != color{};
                }
                
                inline bool valid_decimals(byte decimals) {
                    return decimals <= 9; 
                }
                
                inline bool valid_mint_baton_vout(byte mint_baton_vout) {
                    return mint_baton_vout >= 0x02;
                }
                
                inline bool valid_outputs(vector<quantity> outputs) {
                    N size = outputs.size();
                    return (size >= 1 && size <= max_outputs);
                }
            
                inline bool valid_genesis_input(byte decimals, byte* mint_baton_vout) {
                    return valid_decimals(decimals) && (mint_baton_vout == nullptr ? true : valid_mint_baton_vout(*mint_baton_vout));
                }
            
                inline bool valid_mint_input(color id, byte* mint_baton_vout) {
                    return valid_color(id) && (mint_baton_vout == nullptr ? true : valid_mint_baton_vout(*mint_baton_vout));
                }
            
                inline bool valid_send_input(color id, vector<quantity> outputs) {
                    return valid_color(id) && valid_outputs(outputs);
                }
            
            }
            
            namespace scripts {
            
                inline bool genesis::valid() {
                    return low::valid_token_type(Token) && low::valid_genesis_input(Decimals, MintBatonVout);
                }
                
                inline bool mint::valid() {
                    return low::valid_token_type(Token) && low::valid_mint_input(Color, MintBatonVout);
                }
                
                inline bool send::valid() {
                    return low::valid_token_type(Token) && low::valid_send_input(Color, Outputs);
                }
            
                inline script genesis::write() {
                    if (!low::valid_token_type(Token)) return {};
                    return type_1::genesis(Ticker, Name, DocumentUrl, DocumentHash, Decimals, MintBatonVout, InitialTokenMintQuantity);
                }
                
                inline script mint::write() {
                    if (!low::valid_token_type(Token)) return {};
                    return type_1::mint(Color, MintBatonVout, AdditionalTokenQuantity);
                }
                
                inline script send::write() {
                    if (!low::valid_token_type(Token)) return {};
                    return type_1::send(Color, OutputQuantities);
                }
            
            }
            
        }
    
    }

}

#endif
