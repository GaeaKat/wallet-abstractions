#ifndef ABSTRACTIONS_LOGIC_INTUINISTIC_HPP
#define ABSTRACTIONS_LOGIC_INTUINISTIC_HPP

#include <abstractions/logic/logic.hpp>
#include <abstractions/constant.hpp>
#include <abstractions/operation.hpp>

namespace abstractions
{
    
    namespace logic
    {
        
        // The axioms of intuinistic logic. 
        template <typename A, typename B>
        const Implies<A, Implies<B, A>&>& THEN_1();
        
        template <typename A, typename B, typename C>
        const Implies<Implies<A, Implies<B, C>&>&, Implies<Implies<A, B>&, Implies<A, C>&>&>& THEN_2();
        
        template <typename A, typename B>
        const Implies<And<A, B>&, A>& AND_1();
        
        template <typename A, typename B>
        const Implies<And<A, B>&, B>& AND_2();
        
        template <typename A, typename B>
        const Implies<A, Implies<B, And<A, B>&>&>& AND_3();
        
        template <typename A, typename B>
        const Implies<A, Or<A, B>> OR_1();
        
        template <typename A, typename B>
        const Implies<B, Or<A, B>> OR_2();
        
        template <typename A, typename B>
        const Implies<Implies<A, C>&, Implies<Implies<B, C>&, Implies<Or<A, B>, C>&>&> OR_3();
        
        template <typename X>
        const Implies<contradiction, X> FALSE();
        
        // a representation of intuinistic logic. 
        template <typename A> struct intuinistic;
        
        template <typename A, typename B> 
        struct intuinistic<Implies<A, Implies<B, A>&>> : public Implies<A, Implies<B, A>&> {
            struct constant : public Implies<B, A>, public abstractions::constant<B> {};
            
            Implies<B, A>& operator()(A a) const {
                return *new constant<A>{a};
            }
        };
        
        template <typename A, typename B>
        inline const Implies<A, Implies<B, A>&>& THEN_1() {
            return *new intuinistic<Implies<A, Implies<B, A>&>>{};
        }
        
        template <typename A, typename B, typename C> 
        struct intuinistic<Implies<Implies<A, Implies<B, C>&>&, Implies<Implies<A, B>&, Implies<A, C>&>&>> : public Implies<Implies<A, Implies<B, C>&>&, Implies<Implies<A, B>&, Implies<A, C>&>&> {
            struct operation : public Implies<A, C>, public operation<Implies<A, Implies<B, C>&>&, Implies<A, B>&> {}
            
            struct application : public Implies<Implies<A, B>&, Implies<A, C>&> {
                Implies<A, Implies<B, C>&>& Function;
                
                Implies<A, C>& operator()(Implies<A, B>& x) const {
                    return *new operation{Function, x};
                }
            };
            
            Implies<Implies<A, B>&, Implies<A, C>&>& operator()(Implies<A, Implies<B, C>&>& x) const {
                return *new application<Implies<A, Implies<B, C>&>&>{x};
            }
        };
        
        template <typename A, typename B, typename C>
        inline const Implies<Implies<A, Implies<B, C>&>&, Implies<Implies<A, B>&, Implies<A, C>&>&>& THEN_2() {
            return *new intuinistic<Implies<Implies<A, Implies<B, C>&>&, Implies<Implies<A, B>&, Implies<A, C>&>&>>{};
        }
        
        template <typename A, typename B> 
        struct intuinistic<Implies<And<A, B>&, A>> : public Implies<And<A, B>, A> {                
            A operator()(And<A, B> x) const {
                return x.Left;
            }
        };
        
        template <typename A, typename B>
        inline const Implies<And<A, B>, A>& AND_1() {
            return *new intuinistic<Implies<And<A, B>, A>>{};
        }
        
        template <typename A, typename B> 
        struct intuinistic<Implies<And<A, B>, B>> : public Implies<And<A, B>, B> {                
            A operator()(And<A, B> x) const {
                return x.Right;
            }
        };
        
        template <typename A, typename B>
        inline const Implies<And<A, B>, B>& AND_2() {
            return *new intuinistic<Implies<And<A, B>, B>>{};
        }
        
        template <typename A, typename B> 
        struct intuinistic<Implies<A, Implies<B, And<A, B>>&>> : public Implies<A, Implies<B, And<A, B>>&> {
            struct incomplete_and {
                A Left;
                
                And<A, B> operator()(B b) {
                    return And<A, B>{Left, b};
                }
            };
            
            Implies<B, And<A, B>&>& operator()(A a) const {
                return *new incomplete_and{a};
            }
        };
        
        template <typename A, typename B>
        inline const Implies<A, Implies<B, And<A, B>&>&>& AND_3() {
            return *new intuinistic<Implies<A, Implies<B, And<A, B>&>&>>{};
        }
        
        template <typename A, typename B> 
        struct intuinistic<Implies<A, Or<A, B>>> : public Implies<A, Or<A, B>> {                
            Or<A, B> operator()(A a) const {
                return Or<A, B>{a};
            }
        };
        
        template <typename A, typename B>
        inline const Implies<A, Or<A, B>> OR_1() {
            return *new intuinistic<Implies<A, Or<A, B>>>{};
        }
        
        template <typename A, typename B> 
        struct intuinistic<Implies<B, Or<A, B>>> : public Implies<B, Or<A, B>> {                
            Or<A, B> operator()(B b) const {
                return Or<A, B>{b};
            }
        };
        
        template <typename A, typename B>
        inline const Implies<B, Or<A, B>> OR_2() {
            return *new intuinistic<Implies<B, Or<A, B>>>{};
        }
        
        template <typename A, typename B, typename C> 
        struct intuinistic<Implies<Implies<A, C>&, Implies<Implies<B, C>&, Implies<Or<A, B>, C>&>&>> : public Implies<Implies<A, C>&, Implies<Implies<B, C>&, Implies<Or<A, B>, C>&>&> {                
            Implies<B, A>& operator()(A a) const {
                return *new constant<A>{a};
            }
        };
        
        template <typename A, typename B>
        inline const Implies<Implies<A, C>&, Implies<Implies<B, C>&, Implies<Or<A, B>, C>&>&>& OR_3() {
            return *new intuinistic<Implies<Implies<A, C>&, Implies<Implies<B, C>&, Implies<Or<A, B>&, C>&>&>>{};
        }
        
        template <typename X>
        struct intuinistic<Implies<contradiction, X>> : public Implies<contradiction, X> {
            X Implies<B, A>& operator()(contradiction x) const {
                throw x;
            }
        };
        
        template <typename X>
        inline const Implies<contradiction, X> FALSE() {
            return *new intuinistic<Implies<contradiction, X>>{};
        }
        
    }
    
}

#endif
