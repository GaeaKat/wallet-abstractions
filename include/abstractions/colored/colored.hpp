#ifndef ABSTRACTIONS_COLORED_COLORED_HPP
#define ABSTRACTIONS_COLORED_COLORED_HPP

#include <abstractions/reduce.hpp>

namespace abstractions
{

    namespace colored
    {
        
        template <typename T, typename C>
        using color = C (*) (T tx);
        
        enum transaction_type {none, genesis, mint, send};
        
        template <typename T, typename C>
        using get_type = transaction_type (*)(T);
        
        template <typename C>
        struct value {
            N Quantity;
            C Color;
            
            value() : Quantity(0), Color({}) {}
            
            // You're not allowed to have colored value with zero in it. 
            value(N v, C c) : Quantity(c == C{} ? 0 : v), Color(v == 0 ? 0 : c) {}
            
            value<C> operator+(value<C> x) const {
                if (Color != x.Color) return value();
                
                return value(Quantity + x.Quantity, Color);
            }
            
            bool valid() const {
                Color != C{};
            }
        };
        
        // Data that says how to interpret a TX as a colored tx. 
        template <typename C>
        struct meta {
            transaction_type Type;
            
            C Color;
            
            vector<N> Inputs;
            
            map<N, value<C>> Outputs;
            
            bool valid() const {
                return Type != none && Color != C{};
            }
            
        private:
            meta() : Type(none) {}
        };
        
        template <typename tx, typename C>
        using interpret = meta<C> (*) (tx, C);
        
        template <typename tx, typename point, typename C> struct blockchain;
        
        template <typename tx, typename point, typename C>
        struct transaction {
            // The original Bitcoin transaction. 
            tx Bitcoin;
            
            map<C, meta<C>> Meta;
            
            interpret<tx, C> Interpret;
            
            bool valid() const {
                for (data::maps::entry<C, meta<C>> entry : Meta)
                    if (!(entry.value().valid() && entry.Value == Interpret(Bitcoin, entry.Key))) return false;
                return true;
            }
            
            bool verify(blockchain<tx, point, C>& b) const;
        };

        template <typename tx, typename point, typename C>
        struct output {
            // The original Bitcoin transaction. 
            transaction<tx, point, C> Transaction;
            
            // the index of this output in the original transaction. 
            N Index;
            
            const value<C> value() const {
                return Transaction.Meta.Outputs[Index];
            };
            
            bool valid() const {
                return Transaction.valid() && Index != aleph_0 && value().valid();
            }
            
            bool verify(blockchain<tx, point, C>& b) {
                return Transaction.verify(b);
            }
            
            output() : Index(aleph_0) {}
        };
        
        template <typename tx, typename point, typename C> struct blockchain {
            virtual output<tx, point, C> retrieve(point) const = 0;
            
            // Can be overridden so as to support caching. 
            virtual value<C> value(point p) const {
                return retrieve(p).value();
            }
        };
        
        template <typename tx, typename point, typename C> 
        inline bool verify(blockchain<tx, point, C>& b, point p) {
            return b.retrieve(p).verify(b);
        }
        
        template <typename tx, typename point, typename C> 
        bool verify(const blockchain<tx, point, C>& b, meta<C> m);
        
        template <typename tx, typename point, typename C>
        bool transaction<tx, point, C>::verify(blockchain<tx, point, C>& b) const {
            if (!valid()) return false;
            
            // What is the total C value redeemed by this transaction?
            return verify(b, Meta);
        }
        
    }

}

#endif
