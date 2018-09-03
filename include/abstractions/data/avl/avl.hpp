#ifndef ABSTRACTIONS_TREES_AVL_AVL_HPP
#define ABSTRACTIONS_TREES_AVL_AVL_HPP

#include <abstractions/data/tree.hpp>

namespace abstractions
{
    
    namespace data 
    {
        
        namespace trees
        {
            
            namespace avl
            {
                
                typedef const int16_t balance;
                    
                bool balanced(balance b) {
                    return b < 2 && b > -2;
                }
                
                template <typename X>
                struct node {
                    X Data;
                    balance Balance;

                    tree<X, node<X>> Left;
                    tree<X, node<X>> Right;
                    
                    node(X v, balance b, tree<X, node<X>> n, tree<X, node<X>> l, tree<X, node<X>> r) : Data(v), Balance(b), Left(l), Right(r) {}
                    node(X v) : Data(v), Balance(0), Left(nullptr), Right(nullptr) {}
                };
                
            }
            
        }
        
        template <typename X>
        using avl_tree = tree<X, trees::avl::node<X>>;
        
    }
        
    template<typename X>
    bool valid(data::avl_tree<X>);
    
}

#endif
