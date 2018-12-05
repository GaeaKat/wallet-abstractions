#ifndef ABSTRACTIONS_INVERSE_HPP
#define ABSTRACTIONS_INVERSE_HPP

#include <abstractions/claim.hpp>

namespace abstractions
{
    
    namespace inverse {
        
        template <typename f, typename key, typename value>
        struct test {
            f Function;
            
            bool operator()(key k, value v) {
                return k == Function(v);
            }
            
        };
        
        template <typename f, typename key, typename value>
        using claim = abstractions::claim<test<f, key, value>, key, value>;
        
        template <typename f, typename key, typename value>
        using proof = abstractions::proof<test<f, key, value>, key, value>;
        
        template <typename f, typename key, typename value>
        claim<f, key, value> make_claim(f fun, key k) {
            return {test<f, key, value>{fun}, k};
        }
        
        template <typename f, typename key, typename value>
        proof<f, key, value> prove(f fun, key v, value k) {
            return {make_claim(fun, k), v};
        }
    
    }

}

#endif
