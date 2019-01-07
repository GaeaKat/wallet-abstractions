#ifndef ABSTRACTIONS_LOGIC_LOGIC_HPP
#define ABSTRACTIONS_LOGIC_LOGIC_HPP

#include <truth/identity.hpp>
#include <abstractions/logic/relation.hpp>

namespace abstractions {
    
    namespace logic {
        template <typename A, typename B>
        struct Implies : public relation<A, operand::Implies, B> {
            virtual B operator()(A) const = 0;
        };
            
        template <typename A>
        struct Implies<A, A> : public relation<A, operand::Implies, A>, public identity<A> {};
            
        template <typename A, typename B>
        struct Or : public relation<A, operand::Or, B> {
            Or(A) {}
            Or(B) {}
        };
            
        template <typename A, typename B>
        struct And : public relation<A, operand::And, B> {
            A Left;
            B Right;
                
            And(A a, B b) : Left{a}, Right{b} {}
        };
            
        template <typename A, typename B>
        struct Equal : public Implies<A, B>, public Implies<B, A>, public relation<A, operand::Equal, B> {};
            
        template <typename X>
        struct Equal<X, X> : public Implies<A, A> {};
            
    }

}

namespace truth {
    
    namespace statement {
        
        // Insure an equal statement is read as an equal statement. 
        template <typename X, typename Y>
        struct reader<logic::Equal<X, Y>> {
            string read() const {
                return statement::read<relation<A, operand::Equal, B>>(); 
            }
        };
    
    }
    
}

#endif
