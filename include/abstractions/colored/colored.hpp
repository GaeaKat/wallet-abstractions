#ifndef ABSTRACTIONS_COLORED_COLORED_HPP
#define ABSTRACTIONS_COLORED_COLORED_HPP

#include <abstractions/reduce.hpp>

namespace abstractions
{

    namespace colored
    {
        
        enum transaction_type {none, genesis, mint, send};
        
        template <typename T, typename C>
        using get_type = transaction_type (*)(T);
        
        template <typename C>
        struct value {
            N Quantity;
            C Color;
            
            value() : Quantity(0), Color({}) {}
            
            // You're not allowed to have colored value with zero in it. 
            value(N q, C c) : Quantity{c == C{} ? 0 : q}, Color{q == 0 ? 0 : c} {}
            value(value<C>& v) : Quantity{v.Quantity}, Color{v.Color} {}
            
            value<C> operator+(value<C> x) const {
                if (Color != x.Color) return value();
                
                return value(Quantity + x.Quantity, Color);
            }
            
            bool valid() const {
                Color != C{};
            }
        };
        
        // A value matched with an output. 
        template <typename C>
        struct send_index {
            N Index;
            value<C> Value;
            
            N quantity() const {
                return Value.Quantity;
            }
            
            C color() const {
                return Value.Color;
            }
            
            bool valid() const {
                return Value.valid() && Index != aleph_0;
            }
            
        private:
            send_index() : Value(), Index(aleph_0) {}
            send_index(N i, N q, C c) : Index{i}, Value{q, c} {}
            send_index(N i, value<C> v) : Index{i}, Value{v} {}
        };
        
        // A value matched with an output. 
        template <typename C>
        struct mint_index {
            N Index;
            C Color;
            
            bool valid() const {
                return Color != C{} && Index != aleph_0;
            }
            
        private:
            mint_index() : Color{}, Index(aleph_0) {}
            mint_index(N i, C c) : Index{i}, Color{c} {}
        };
        
        // Data that says how to interpret a TX as a colored tx. 
        template <typename C, typename out>
        struct meta {
            transaction_type Type;
            
            C Color;
            
            map<N, value<C>> Send;
            
            map<N, C> Mint;
            
            bool valid() const {
                if (!(Type != none && Color != C{})) return false;
                for (map<N, value<C>>::entry e : Send) if (!send_index<C>{e.Key, e.Value}.valid()) return false;
                for (map<N, C>::entry e : Mint) if (!mint_index<C>{e.Key, e.Value}.valid()) return false;
                return true;
            }
            
            meta() : Type(none) {}
            meta(transaction_type t, C c, map<N, value<C>> s, map<N, C> m) : Type{t}, Color{c}, Send{s}, Mint{m} {}
        };
        
        template <typename tx, typename out, typename C>
        using interpret = meta<C, out> (*) (tx, C);
        
        template <typename tx, typename point, typename out, typename C> struct blockchain;
        
        template <typename tx, typename point, typename out, typename C>
        struct transaction {
            // The original Bitcoin transaction. 
            tx Bitcoin;
            
            map<C, meta<C, out>> Meta;
            
            //interpret<tx, C> Interpret;
            
            bool valid() const {
                for (data::maps::entry<C, meta<C, out>> entry : Meta)
                    if (!(entry.value().valid() && entry.Value == Interpret(Bitcoin, entry.Key))) return false;
                return true;
            }
            
            bool verify(blockchain<tx, point, out, C>& b) const;
        };

        template <typename tx, typename point, typename out, typename C>
        struct output {
            // The original Bitcoin transaction. 
            transaction<tx, point, out, C> Transaction;
            
            // the index of this output in the original transaction. 
            N Index;
            
            const value<C> value() const {
                return Transaction.Meta.Outputs[Index];
            };
            
            bool valid() const {
                return Transaction.valid() && Index != aleph_0 && value().valid();
            }
            
            bool verify(blockchain<tx, point, out, C>& b) {
                return Transaction.verify(b);
            }
            
            output() : Index(aleph_0) {}
        };
        
        template <typename tx, typename point, typename out, typename C> struct blockchain {
            virtual output<tx, point, out, C> retrieve(point) const = 0;
            
            // Can be overridden so as to support caching. 
            virtual value<C> value(point p) const {
                return retrieve(p).value();
            }
        };
        
        template <typename tx, typename point, typename out, typename C> 
        inline bool verify(blockchain<tx, point, out, C>& b, point p) {
            return b.retrieve(p).verify(b);
        }
        
        template <typename tx, typename point, typename out, typename C> 
        bool verify(const blockchain<tx, point, out, C>& b, meta<C, out> m);
        
        template <typename tx, typename point, typename out, typename C>
        bool transaction<tx, point, out, C>::verify(blockchain<tx, point, out, C>& b) const {
            if (!valid()) return false;
            
            // What is the total C value redeemed by this transaction?
            return verify(b, Meta);
        }
        
    }

}

#endif
