#ifndef ABSTRACTIONS_DATA_TREE_HPP
#define ABSTRACTIONS_DATA_TREE_HPP

#include <abstractions/data/list.hpp>
#include <abstractions/data/set.hpp>

namespace abstractions {
    
    namespace data {
        
        namespace tree {
            
            namespace definition {
                    
                template <typename T>
                struct tree : public set::definition::existence<T> {
                    T left(T t) const {
                        return t.left();
                    }
                        
                    T right(T t) const {
                        return t.right();
                    }
                };
                    
                template <typename T>
                struct tree<T*> : public set::definition::existence<T*> {
                    T left(T t) const {
                        if (t == nullptr) return nullptr;
                        return t->left();
                    }
                        
                    T right(T t) const {
                        if (t == nullptr) return nullptr;
                        return t->right();
                    }
                };
                    
                template <typename T>
                struct tree<pointer<T>> : public set::definition::existence<pointer<T>> {
                    T left(T t) const {
                        if (t == nullptr) return nullptr;
                        return t->left();
                    }
                        
                    T right(T t) const {
                        if (t == nullptr) return nullptr;
                        return t->right();
                    }
                };
                    
                template <typename T, typename X>
                struct set : public data::set::definition::set<T, X> {
                    X& root(T t) const {
                        return t.root();
                    }
                };
                    
                template <typename T, typename X>
                struct set<T*, X> : public data::set::definition::set<T*, X> {
                    X& root(T t) const {
                        return t->root();
                    }
                };
                    
                template <typename T, typename X>
                struct set<pointer<T>, X> : public data::set::definition::set<pointer<T>, X> {
                    X& root(T t) const {
                        return t->root();
                    }
                };
                    
                template <typename T, typename X>
                struct removable : public data::set::definition::removable<T, X>, public set<T, X> , public tree<T> {};
                    
                template <typename T, typename X>
                struct insertable : public data::set::definition::insertable<T, X>, public set<T, X>, public tree<T> {};

                template <typename T, typename X, typename L>
                struct countable : public data::set::definition::countable<T, X, L>, public set<T, X>, public tree<T> {}; 
                
            }
            
            template <typename T, typename X>
            inline X& root(const T t) {
                return definition::set<T, X>{}.root(t);
            }
                
            template <typename T>
            inline T right(const T t) {
                return definition::tree<T>{}.right(t);
            }
                
            template <typename T>
            inline T left(const T t) {
                return definition::tree<T>{}.left(t);
            }

            template <typename A>
            inline bool empty(A a) {
                return set::definition::existence<A>{}.empty(a);
            }

            template <typename A, typename X> 
            inline bool contains(A a, X x) {
                return definition::set<A, X>{}.contains(a, x);
            }

            template <typename A, typename X> 
            inline A remove(A a, X x) {
                return definition::removable<A, X>{}.remove(a, x);
            }

            template <typename A, typename X> 
            inline A insert(A a, X x) {
                return definition::insertable<A, X>{}.insert(a, x);
            }

            template <typename A, typename X, typename L> 
            inline L members(A a) {
                return definition::countable<A, X, L>{}.members(a);
            }
                
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
            struct binary {
                pointer<node<X, binary<X>>> Tree;
                
                bool empty() const {
                    return Tree == nullptr;
                }
                
                X& first() const {
                    return Tree->First;
                }
                
                binary right() const {
                    return Tree->Right;
                }
                
                binary left() const {
                    return Tree->Left;
                }
                
                bool contains(X x) const {
                    if (empty()) return false;
                    return Tree->contains(x);
                }
            };
            
        }
    
    }

}

#endif
