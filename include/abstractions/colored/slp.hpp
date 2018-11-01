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
            
            namespace low {
                
                using reader = const abstractions::reader;
            
                const byte max_byte = 0xff;
                const uint32_t max_uint32 = 0xffff;
                const quantity max_quantity = 0xffffffff;
                
                inline N push_size(uint32_t size) {
                    if (size == 0) return 2;
                    if (size <= max_push) return size + 1;
                    if (size <= max_byte) return size + 2;
                    if (size <= max_uint32) return size + 3;
                    if (size <= max_quantity) return size + 5;
                    return 0;
                }
                
                reader read_empty_push(reader r);
                
                reader read_push_size(reader r, uint64_t&);
                
                reader read_value(reader, byte& b, N size);
                
                reader read_value(reader, uint32_t& b, N size);
                
                reader read_value(reader, token_type& b, N size);
                
                reader read_value(reader, color& b, N size);
                
                reader read_value(reader, hash& b, N size);
                
                reader read_value(reader, quantity& b, N size);
                
                reader read_value(reader, encoding::ascii::string& b, N size);
                
                reader read_value(reader, encoding::utf8::string& b, N size);
                
                template <typename X>
                inline reader read_push(reader r, X& x) {
                    uint64_t size;
                    return read_value(read_push_size(r, size), x, size);
                }
                
                template <typename X>
                reader read_push_optional(reader r, optional<X>& x) {
                    uint64_t size;
                    reader rr = read_push_size(r, size);
                    
                    if (size == 0) {
                        x.Exists = false;
                        return read_empty_push(r);
                    }
                    
                    x.Exists = true;
                    return read_value(rr, x.Value, size);
                }
                
            }
            
            template <typename X>
            struct push_script_pattern {
                X Value;
                
                push_script_pattern(X x) : Value(x) {}
                
                low::reader apply(low::reader r) {
                    X x;
                    reader rr = low::read_push(r, x);
                    return Value == x ? rr : rr.invalidate(); 
                }
            };
            
            template <typename X>
            struct push_script_pattern<X&> {
                X& Value;
                
                push_script_pattern(X& x) : Value(x) {}
                
                low::reader apply(low::reader r) {
                    return low::read_push(r, Value);
                }
            };
            
            template <typename X>
            struct push_script_pattern<optional<X>&> {
                optional<X>& Value;
                
                push_script_pattern(optional<X>& x) : Value(x) {}
                
                low::reader apply(low::reader r) {
                    return low::read_push_optional(r, Value);
                };
            };
            
            template <typename X>
            push_script_pattern<X> push(X x) {
                return push_script_pattern<X>{x};
            }
            
            template <typename X>
            push_script_pattern<X&> read_push(X& x) {
                return push_script_pattern<X&>(x);
            }
            
            class reader {
                low::reader r;
                reader(low::reader x) : r(x) {}
                
            public:
                
                static reader make(script& s) {
                    return reader(abstractions::reader(slice<byte>(s)));
                }
                
                bool end() const {
                    return r.end();
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
                
                reader operator>>(push_script_pattern<byte&> sc);
                
                reader operator<<(push_script_pattern<uint32_t> sc);
                
                reader operator<<(push_script_pattern<token_type>);
                
                reader operator<<(push_script_pattern<encoding::ascii::string>);
                
                reader operator>>(push_script_pattern<color&>);
                
                reader operator>>(push_script_pattern<quantity&>);
                
                reader operator>>(push_script_pattern<encoding::ascii::string&>);
                
                reader operator>>(push_script_pattern<encoding::utf8::string&>);
                
                reader operator>>(push_script_pattern<optional<byte>&>);
                
                reader operator>>(push_script_pattern<optional<hash>&>);
            };
                
            template <typename X> reader read_all(reader r, vector<X>& l);
                    
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
                    return read_all(reader::make(s) << op_return << push(lokad) << push(permissionless) << push(send_string)
                        >> read_push(x.Color), x.OutputQuantities).valid() ? x : send{};
                }
            
            }
            
        }
    
    }

}

#endif
