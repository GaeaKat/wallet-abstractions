#ifndef ABSTRACTIONS_COLORED_HPBOC_HPP
#define ABSTRACTIONS_COLORED_HPBOC_HPP

#include <abstractions/colored/colored.hpp>
#include <abstractions/encoding/ascii.hpp>
#include <abstractions/encoding/utf8.hpp>
#include <abstractions/blockchain/transaction.hpp>
#include <abstractions/blockchain/output.hpp>
#include <abstractions/optional.hpp>

namespace abstractions
{
    
    namespace colored
    {
        
        namespace slp {
            
            // get metadata for a tx of a given color. 
            template <typename tx, typename C>
            meta<C> interpret(tx, C);
            
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
                    encoding::utf8::string Ticker;
                    encoding::utf8::string Name;
                    encoding::ascii::string DocumentUrl;
                    optional<hash> DocumentHash;
                    byte Decimals;
                    optional<byte> MintBatonVout;
                    quantity InitialTokenMintQuantity;
                    
                    bool valid();
                        
                    script write();
                    
                    genesis() : Token(none), Ticker{}, Name{}, DocumentUrl{}, DocumentHash(), Decimals(0), MintBatonVout(), InitialTokenMintQuantity(0) {}
                    genesis(unicode x, unicode n, encoding::ascii::string u, hash h, byte d, byte m, quantity q)
                        : Token(permissionless), Ticker(encoding::utf8::write(x)), Name(encoding::utf8::write(n)),
                            DocumentUrl(u), DocumentHash(h), Decimals(d), MintBatonVout(m), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, encoding::ascii::string u, hash h, byte d, quantity q)
                        : Token(permissionless), Ticker(encoding::utf8::write(x)), Name(encoding::utf8::write(n)),
                            DocumentUrl(u), DocumentHash(h), Decimals(d), MintBatonVout(), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, byte d, byte m, quantity q)
                        : Token(permissionless), Ticker(encoding::utf8::write(x)), Name(encoding::utf8::write(n)),
                            DocumentUrl(""), DocumentHash(), Decimals(d), MintBatonVout(m), InitialTokenMintQuantity(q) {}
                    genesis(token_type t, unicode x, unicode n, byte d, quantity q)
                        : Token(t), Ticker(encoding::utf8::write(x)), Name(encoding::utf8::write(n)),
                            DocumentUrl(""), DocumentHash(), Decimals(d), MintBatonVout(), InitialTokenMintQuantity(q) {}
                    
                    static const genesis read(script);
                };
                    
                struct mint {
                    token_type Token;
                    color Color; 
                    optional<byte> MintBatonVout;
                    quantity AdditionalTokenQuantity;
                    
                    bool valid();
                        
                    script write();
                    
                    mint() : Token(none), Color(), MintBatonVout(), AdditionalTokenQuantity(0) {};
                    
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
            
            using ascii = encoding::ascii::string;
            
            namespace type_1 {
                
                script genesis(
                    encoding::utf8::string ticker,
                    encoding::utf8::string name,
                    ascii document_url,
                    optional<hash> document_hash,
                    byte decimals, 
                    optional<byte> mint_baton_vout,
                    quantity initial_token_mint_quantity);
                
                inline script genesis(
                    unicode ticker,
                    unicode name,
                    ascii document_url,
                    optional<hash> document_hash,
                    byte decimals, 
                    optional<byte> mint_baton_vout,
                    quantity initial_token_mint_quantity) {
                    return genesis(
                        encoding::utf8::write(ticker), 
                        encoding::utf8::write(name),
                        document_url, document_hash, decimals, mint_baton_vout, initial_token_mint_quantity);
                }
                
                script mint(
                    color id, 
                    optional<byte> mint_baton_vout,
                    quantity additional_token_quantity);
                
                script send(
                    color id, 
                    vector<quantity> output_quantities);
                
            }
            
            // Some constants which will be important. 
            const byte op_return = 0x6a;
            
            const byte min_push = 0x01;
            const byte max_push = 0x4b;
            
            // A thing that has to go in every script. 
            const uint32_t lokad = 0x534c5000;
            
            const endian::ness endian = endian::big;
            
            const byte push_data_1 = 0x4c;
            const byte push_data_2 = 0x4d;
            const byte push_data_4 = 0x4e;
            
            const encoding::ascii::string genesis_string = std::string("GENESIS");
            const encoding::ascii::string mint_string = std::string("MINT");
            const encoding::ascii::string send_string = std::string("SEND");
            
            const N max_outputs = 19;
            
            template <typename X>
            struct push_script {
                X Value;
                bool Optional;
                
                push_script(X x) : Value(x), Optional(false) {}
                push_script(X x, bool o) : Value(x), Optional(o) {}
            };
            
            template <typename X>
            push_script<X> push(X x) {
                return push_script<X>{x};
            }
            
            template <typename X>
            push_script<X&> read_push(X& x) {
                return push_script<X&>(x);
            }
            
            class reader {
                abstractions::reader r;
                reader(abstractions::reader x) : r(x) {}
                
            public:
                
                static reader make(script& s) {
                    return reader(abstractions::reader(slice<byte>(s)));
                }
                
                bool valid() const {
                    return r.Valid;
                };
                
                reader operator<<(byte b) {
                    return reader{r.check(b)};
                }
                
                reader operator>>(byte& b) {
                    return reader{r.read(b)};
                }
                
                reader operator>>(push_script<byte&>);
                
                reader operator<<(push_script<uint32_t>); 
                
                reader operator<<(push_script<token_type>);
                
                reader operator<<(push_script<encoding::ascii::string>);
                
                reader operator>>(push_script<color&>);
                
                reader operator>>(push_script<quantity&>);
                
                reader operator>>(push_script<encoding::ascii::string&>);
                
                reader operator>>(push_script<encoding::utf8::string&>);
                
                reader operator>>(push_script<optional<byte>&>);
                
                reader operator>>(push_script<optional<hash>&>);
            };
                    
            namespace scripts {
                
                const genesis genesis::read(script s) {
                    genesis x{};
                    x.Token = permissionless;
                    return (reader::make(s) << op_return << push(lokad) << push(permissionless) << push(genesis_string)
                        >> read_push(x.Ticker) >> read_push(x.Name) >> read_push(x.DocumentHash) >> read_push(x.Decimals)
                        >> read_push(x.MintBatonVout) >> read_push(x.InitialTokenMintQuantity)).valid() ? x : genesis{};
                    
                }
                
                const mint mint::read(script s) {
                    mint x{};
                    x.Token = permissionless;
                    return (reader::make(s) << op_return << push(lokad) << push(permissionless) << push(mint_string)
                        >> read_push(x.Color) >> read_push(x.MintBatonVout) >> read_push(x.AdditionalTokenQuantity)).valid() ? x : mint{};
                }
                
                const send send::read(script s) {
                    send x{};
                    x.Token = permissionless;
                    reader r = reader::make(s) << op_return << push(lokad) << push(permissionless) << push(send_string)
                        >> read_push(x.Color) ;
                    do {
                        quantity q;
                        r = r >> read_push(q);
                    } while(!r.end());
                    return r.valid() ? x : send{};
                }
            
            }
            
        }
    
    }

}

#endif
