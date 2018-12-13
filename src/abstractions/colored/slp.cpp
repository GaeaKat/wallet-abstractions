#include <abstractions/colored/slp.hpp>
#include <abstractions/data.hpp>
            
namespace abstractions
{

    namespace colored
    {
        
        namespace slp {
            
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
                    encoding::utf8::string ticker,
                    encoding::utf8::string name, 
                    byte decimals,
                    optional<byte> mint_baton_vout) {
                    return ticker != encoding::utf8::string{} && name != encoding::utf8::string{} && valid_decimals(decimals)
                        && mint_baton_vout.valid();
                }
            
                inline bool valid_mint_input(color id, optional<byte> mint_baton_vout) {
                    return valid_color(id) && mint_baton_vout.valid();
                }
            
                inline bool valid_send_input(color id, vector<quantity> outputs) {
                    return valid_color(id) && valid_outputs(outputs);
                }
            
            }
            
            inline bool genesis::valid() const {
                return low::valid_token_type(Token) && low::valid_genesis_input(Ticker, Name, Decimals, MintBatonVout);
            }
                
            inline bool mint::valid() const {
                return low::valid_token_type(Token) && low::valid_mint_input(Color, MintBatonVout);
            }
                
            inline bool send::valid() const {
                return low::valid_token_type(Token) && low::valid_send_input(Color, OutputQuantities);
            }
            
            inline script genesis::write() const {
                if (!low::valid_token_type(Token)) return {};
                return type_1::genesis(Ticker, Name, DocumentUrl, DocumentHash, Decimals, MintBatonVout, InitialTokenMintQuantity);
            }
                
            inline script mint::write() const {
                if (!low::valid_token_type(Token)) return {};
                return type_1::mint(Color, MintBatonVout, AdditionalTokenQuantity);
            }
                
            inline script send::write() const {
                if (!low::valid_token_type(Token)) return {};
                return type_1::send(Color, OutputQuantities);
            }
            
            inline writer write_empty_push(writer w) {
                return w.write(push_data_1).write(byte(0));
            }
            
            writer write_push(writer w, uint32_t size) {
                if (size == 0) return write_empty_push(w);
                if (size <= max_push) return w.write(byte(size));
                if (size <= max_push) return w.write(push_data_1).write(byte(size));
                if (size <= low::max_uint32) return w.write(push_data_2).write(endian, uint16_t(size));
                if (size <= low::max_quantity) return w.write(push_data_4).write(endian, uint32_t(size));
            }
                
            inline writer write_op_return(writer w) {
                return w.write(slp::op_return);
            }
            
            inline writer write(writer w, byte b) {
                return write_push(w, 1).write(b);
            }
                
            inline writer write(writer w, hash h) {
                writer ww = write_push(w, 32);
                for (byte b : h) ww = ww.write(b);
                return ww;
            }
            
            template <typename X>
            inline writer write(writer w, optional<X> b) {
                if (b.Exists) return write(w, b.Value);
                return write_empty_push(w);
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
                
            inline writer write_string(writer w, ascii s) {
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
            
            inline writer write_token_type(writer w, uint16_t t) {
                if (t <= low::max_byte) return write_push(w, 1).write(byte(t));
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
                    case transaction_type::genesis:
                        write_string(w, genesis_string);
                        return w;
                    case transaction_type::mint:
                        write_string(w, mint_string);
                        return w;
                    case transaction_type::send:
                        write_string(w, send_string);
                        return w;
                }
            }
            
            inline writer initial_script(bytestring b) {
                return write_token_type(write_lokad_id(write_op_return(writer::make(b))), permissionless);
            }
            
            namespace type_1 {
                
                script genesis(
                    encoding::utf8::string ticker,
                    encoding::utf8::string name,
                    encoding::ascii::string document_url,
                    optional<hash> document_hash,
                    byte decimals, 
                    optional<byte> mint_baton_vout,
                    quantity initial_mint_quantity) {
                        
                    if (!low::valid_genesis_input(ticker, name, decimals, mint_baton_vout)) return {};
                        
                    N size = 1 + 5 + 2 + 7 + 
                        low::push_size(ticker.size()) + 
                        low::push_size(name.size()) + 
                        low::push_size(document_url.size()) +
                        (document_hash.Exists ? 33 : 0) + 2 +
                        (mint_baton_vout.Exists ? 2 : 0) + 9;
                            
                    std::vector<byte> scr(size); 
                    auto s = bytestring(scr);
                    
                    writer w = initial_script(s);
                    w = write_transaction_type(w, colored::genesis);
                    w = write_string(w, ticker);
                    w = write_string(w, name);
                    w = write_string(w, document_url);
                    w = write(w, document_hash);
                    w = write(w, decimals);
                    w = write(w, mint_baton_vout);
                    w = write(w, initial_mint_quantity);
                        
                    return scr;
                }
                    
                script mint(
                    hash id, 
                    optional<byte> mint_baton_vout,
                    quantity additional_token_quantity) {
                    
                    if (!low::valid_mint_input(id, mint_baton_vout)) return {};
                    
                    N size = 1 + 5 + 2 + 5 + 33 + (mint_baton_vout.Exists ? 2 : 0) + 9;

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
            
            }
            
            struct tx_data {
                color Color;
                transaction_type TxType;
                bool Valid;
                
                static tx_data read(script x) {
                    color c = get_color(x);
                    transaction_type t = get_transaction_type(x);
                    
                    if (c != color{} && t != transaction_type::none) return tx_data(c, t);
                    return tx_data();
                }
                
            private :
                tx_data(color c, transaction_type t) : Color(c), TxType(t), Valid(true) {}
                tx_data() : Color{}, Valid(false) {}
            };
            
            template <typename tx, typename out, typename sh>
            meta<color, out> get_meta(tx t) {
                script scr = get_slp_script(t);
                tx_data txd = tx_data::read(scr);
                if (!txd.Valid) return meta<color, out>{};
                auto o = outs(t);

                map<N, value<color>> sends{};
                map<N, color> mints{};
                
                switch (txd.TxType) {
                    default:
                    case none:
                        return meta<color, out>{};
                    case transaction_type::genesis: {
                        const genesis g = genesis::read(scr);
                        sends = sends.insert(1, value<color>{g.InitialTokenMintQuantity, txd.Color}); 
                        if (g.MintBatonVout.Exists && o.size() > g.MintBatonVout.Value) mints = mints.insert(g.MintBatonVout.Value, txd.Color);
                        break;
                    }
                    case transaction_type::mint: {
                        const mint m = mint::read(scr);
                        if (m.MintBatonVout.Exists && o.size() > m.MintBatonVout.Value) mints = mints.insert(m.MintBatonVout.Value, txd.Color);
                        break;
                    }
                    case transaction_type::send: {
                        const send d = send::read(scr);
                        uint n = 1;
                        for (quantity q : d.OutputQuantities) {
                            sends = sends.insert(n, value<color>{q, txd.Color});
                            n ++;
                        }
                        break;
                    }
                }
                
                return meta<color, out>{txd.TxType, txd.Color, sends, mints};
            }
                
        }
        
    }

}
