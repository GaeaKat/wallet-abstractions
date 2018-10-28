#include <abstractions/colored/slp.hpp>
            
namespace abstractions
{

    namespace colored
    {
        
        namespace slp {
            
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
            
                inline bool valid_genesis_input(
                    unicode ticker,
                    unicode name, 
                    byte decimals,
                    byte* mint_baton_vout) {
                    return ticker != unicode{} && name != unicode{} && valid_decimals(decimals)
                        && (mint_baton_vout == nullptr ? true : valid_mint_baton_vout(*mint_baton_vout));
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
                    return low::valid_token_type(Token) && low::valid_genesis_input(Ticker, Name, Decimals, MintBatonVout);
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
            
            inline writer write_empty_push(writer w) {
                return w.write(push_data_1).write(byte(0));
            }
            
            writer write_push(writer w, uint32_t size) {
                if (size == 0) return write_empty_push(w);
                if (size <= max_push) return w.write(byte(size));
                if (size <= max_push) return w.write(push_data_1).write(byte(size));
                if (size <= max_uint32) return w.write(push_data_2).write(endian, uint16_t(size));
                if (size <= max_quantity) return w.write(push_data_4).write(endian, uint32_t(size));
            }
                
            inline writer write_op_return(writer w) {
                return w.write(slp::op_return);
            }
            
            inline writer write(writer w, byte b) {
                return write_push(w, 1).write(b);
            }
                
            inline writer write(writer w, uint16_t i) {
                return write_push(w, 2).write(endian, i);
            }
                
            inline writer write(writer w, uint32_t i) {
                return write_push(w, 4).write(endian, i);
            }
                
            inline writer write(writer w, uint64_t i) {
                return write_push(w, 8).write(endian, i);
            }
                
            inline writer write_string(writer w, encoding::ascii::string s) {
                return write_push(w, s.size()).write(s);
            }
                
            inline writer write_string(writer w, encoding::utf8::string s) {
                return write_push(w, s.size()).write(s);
            }
                
            inline writer write(writer w, byte* b) {
                if (b == nullptr) return w;
                return write(w, *b);
            }
            
            inline writer write_hash(writer w, hash h) {
                writer x = write_push(w, 32);
                for (byte b : h) {
                    x = x.write(b);
                }
                return x;
            }
            
            inline writer write_hash(writer w, hash* h) {
                if (h == nullptr) return w;
                return write_hash(w, *h);
            }
            
            inline writer write_token_type(writer w, uint16_t t) {
                if (t <= max_byte) return write_push(w, 1).write(byte(t));
                return write_push(w, 2).write(t);
            }
            
            inline writer write_lokad_id(writer w) {
                return write(w, lokad);
            }
            
            inline writer write_transaction_type(writer w, transaction_type t) {
                switch (t) {
                    default:
                    case none:
                        return w;
                    case genesis:
                        write_string(w, genesis_string);
                        return w;
                    case mint:
                        write_string(w, mint_string);
                        return w;
                    case send:
                        write_string(w, send_string);
                        return w;
                }
            }
            
            inline writer initial_script(bytestring b) {
                return write_token_type(write_lokad_id(write_op_return(writer::make(b))), permissionless);
            }
                
            script genesis(
                unicode ticker,
                unicode name,
                encoding::ascii::string document_url,
                hash* document_hash,
                byte decimals, 
                byte* mint_baton_vout,
                quantity initial_mint_quantity) {
                    
                if (!low::valid_genesis_input(ticker, name, decimals, mint_baton_vout)) return {};
                    
                // Get size of encoded output. 
                encoding::utf8::string ticker_encoded = encoding::utf8::write(ticker);
                encoding::utf8::string name_encoded = encoding::utf8::write(name);
                    
                if (ticker != unicode{} && ticker_encoded == encoding::utf8::string{}) return {};
                if (name != unicode{} && name_encoded == encoding::utf8::string{}) return {};
                    
                N size = 1 + 5 + 2 + 7 + 
                    push_size(ticker_encoded.size()) + 
                    push_size(name_encoded.size()) + 
                    push_size(document_url.size()) +
                    (document_hash == nullptr ? 0 : 33) + 2 +
                    (mint_baton_vout == nullptr ? 0 : 2) + 9;
                        
                std::vector<byte> scr(size); 
                auto s = bytestring(scr);
                
                writer w = initial_script(s);
                w = write_transaction_type(w, colored::genesis);
                w = write_string(w, ticker_encoded);
                w = write_string(w, name_encoded);
                w = write_string(w, document_url);
                w = write_hash(w, document_hash);
                w = write(w, decimals);
                w = write(w, mint_baton_vout);
                w = write(w, initial_mint_quantity);
                    
                return scr;
            }
                
            script mint(
                hash id, 
                byte* mint_baton_vout,
                quantity additional_token_quantity) {
                
                if (!low::valid_mint_input(id, mint_baton_vout)) return {};
                
                N size = 1 + 5 + 2 + 5 + 33 + (mint_baton_vout == nullptr ? 0 : 2) + 9;

                std::vector<byte> scr(size); 
                auto s = bytestring(scr);
                
                writer w = initial_script(s);
                w = write_transaction_type(w, colored::mint);
                w = write_hash(w, id);
                w = write(w, mint_baton_vout);
                w = write(w, additional_token_quantity);
                    
                return scr;
            }
                
            script send(
                hash id, 
                vector<quantity> output_quantities) {
                
                if (!low::valid_send_input(id, output_quantities)) return {};
                
                N outputs = output_quantities.size();
                N size = 1 + 5 + 2 + 5 + 33 + outputs * 9;
                
                std::vector<byte> scr(size); 
                auto s = bytestring(scr);
        
                writer w = initial_script(s);
                w = write_transaction_type(w, colored::send);
                w = write_hash(w, id);
                for (quantity q : output_quantities) w = write(w, q);

                return scr;
            }
            
            namespace scripts {
                
                const genesis genesis::read(script s) {
                    
                }
                
                const mint mint::read(script s) {
                    
                }
                
                const send send::read(script s) {
                    
                }
            
            }
                
        }
        
    }

}
