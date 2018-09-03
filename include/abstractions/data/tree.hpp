#ifndef ABSTRACTIONS_TREES_TREE_HPP
#define ABSTRACTIONS_TREES_TREE_HPP

#include <abstractions/invalid.hpp>

namespace abstractions
{
    namespace data
    {
            
        template <typename X, typename Y> struct tree;
            
        template <typename X, typename Y>
        inline bool contains(const tree<X, Y> t, X x) {
            if (t == nullptr) return false;
            
            if (x == t->Data) return true;
            
            if (x < t->Data) return contains(t->Left);
                
            return contains(t->Right);
        }
        
        namespace trees {
            
            template <typename X>
            struct node {
                X Data;

                tree<X, node<X>> Left;
                tree<X, node<X>> Right;
                
                node(X v, tree<X, node<X>> n, tree<X, node<X>> l, tree<X, node<X>> r) : Data(v), Left(l), Right(r) {}
                node(X v) : Data(v), Left(nullptr), Right(nullptr) {}
                
            };
            
        }

        template <typename X>
        tree<X, trees::node<X>> insert(const tree<X, trees::node<X>> t, X x) {
            if (t == nullptr) return std::shared_ptr<trees::node<X>>(std::make_shared(trees::node<X>(x)));
            
            if (x == t->Data) return t;
            
            if (x < t->Data) return std::shared_ptr<trees::node<X>>(std::make_shared(trees::node<X>(t->Data, insert(t->Left, x), t->Right)));
            
            return std::shared_ptr<trees::node<X>>(std::make_shared(trees::node<X>(t->Data, t->Left, insert(t->Right, x))));
        };

        template <typename X, typename Y>
        struct tree : public pointer<Y> {
            tree<X, Y> operator+(X x) const {
                return insert(this, x);
            }
            
            /*tree<X, Y> operator-(X x) const {
                return remove(this, x);
            }*/
        };
        
        template <typename X>
        using binary_search_tree = tree<X, trees::node<X>>;
        
    }

}

#endif
