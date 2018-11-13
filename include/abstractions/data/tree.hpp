#ifndef ABSTRACTIONS_DATA_TREE_HPP
#define ABSTRACTIONS_DATA_TREE_HPP

#include <abstractions/data/list.hpp>

namespace abstractions {
    
    namespace data {
        
        namespace tree {
                
            template <typename X, typename T>
            struct node {
                X Data;

                T Left;
                T Right;
                    
                node(X v, T n, T l, T r) : Data(v), Left(l), Right(r) {}
                node(X v) : Data(v), Left{}, Right{} {}
                
                X& first() const {
                    return Data;
                }
                
                T& right() const {
                    return Right;
                }
                
                T& left() const {
                    return Left;
                }
                
                bool contains(X x) const {
                    if (Data == x) return true;
                    if (x < Data) return contains(Left, x);
                    if (x > Data) return contains(Right, x);
                    return false;
                }
                
            };
            
            template <typename F, typename X, typename T>
            X find(F f, T t) {
                if (empty(t)) return X{};
                
                auto i = first(t);
                auto u = f(i);
                if (u < 0) return find(f, right(t));
                if (u > 0) return find(f, left(t));
                if (u == 0) return i;
            }
                
            template <typename X, typename T, typename L>
            struct list {
                T Tree;
                L Previous;
                    
                list(T t, L p) : Tree(t), Previous(p) {}
                list(T t) : Tree(t), Previous{} {}
                list() : Tree{}, Previous{} {}
                
                bool empty() const {
                    return empty(Tree) && empty(Previous);
                }
                
                X& first() const {
                    if (!empty(Tree)) return first(Tree);
                    
                    return first(first(Previous));
                }
                
                list rest() const {
                    if (!empty(Tree)) return list{right(Tree), Previous + left(Tree)};
                    
                    if (!empty(Previous)) return list{first(Previous), rest(Previous)};
                    
                    return list{};
                }
    
                list& operator=(list i) {
                    Tree = i.Tree;
                    Previous = i.Previous;
                    return *this;
                }

            };

            template <typename X, typename T, typename L>
            data::list::iterator<list<X, T, L>, X> begin(T t) {
                return data::list::iterator<list<X, T, L>, X>{list<X, T, L>{t, {}}};
            }
            
            template <typename X, typename T, typename L>
            data::list::iterator<list<X, T, L>, X> end() {
                return data::list::iterator<list<X, T, L>, X>{list<X, T, L>{}};
            }
            
            template <typename X>
            struct linked {
                pointer<node<X, linked<X>>> Tree;
                
                bool empty() const {
                    return Tree == nullptr;
                }
                
                X& first() const {
                    return Tree->First;
                }
                
                linked right() const {
                    return Tree->Right;
                }
                
                linked left() const {
                    return Tree->Left;
                }
                
                bool contains(X x) const {
                    if (empty()) return false;
                    return Tree->contains(x);
                }
            };
            
        }
    
    }
        
    template <typename X>
    X& first(const data::tree::linked<X> t) {
        return t.first();
    }
        
    template <typename X>
    const data::tree::linked<X> right(const data::tree::linked<X> t) {
        return t.right();
    }
        
    template <typename X>
    const data::tree::linked<X> left(const data::tree::linked<X> t) {
        return t.left();
    }

}

#endif
