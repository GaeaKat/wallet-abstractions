#include <abstractions/data/avl.hpp>
#include <tuple>

namespace abstractions
{
    namespace data
    {
    
        namespace trees
        {
            
            namespace avl
            {
                
                struct valid_and_height {
                    bool Valid;
                    uint32_t Height;
                };
                
                typedef uint32_t height;
                
                template<typename X>
                valid_and_height valid(avl_tree<X> t) {
                    if (t == nullptr) return {true, 0};
                    
                    balance m = t->Meta;
                    if (!balanced(m)) return {false, 0};
                    
                    valid_and_height left = valid_height(t->Left);
                    if (!left.Valid) return {false, 0};
                    
                    valid_and_height right = valid_height(t->Right);
                    if (!right.Valid) return {false, 0};
                    
                    if (right.Height - left.Height != t->Meta.Balance) return {false, 0};
                    
                    return {true, 1 + (left.Height > right.Height ? left.Height : right.Height)};
                }
            
                template<typename X>
                avl_tree<X> rotate_left(avl_tree<X> z) {
                    if (z == nullptr) return nullptr;
                    
                    avl_tree<X> y = z->Left;
                    if (y == nullptr) return nullptr;
                    
                    return std::shared_ptr<node<X>>(std::make_shared(node<X>(
                        y->Key, y->Value, 0, y->Left,
                        std::shared_ptr<node<X>>(std::make_shared(node<X>(
                            z->Key, z->Value,
                            y->Meta.Balance < 0 ? 1 : 0,
                            y->Right, z->Left))))));
                }
                
                template<typename X>
                avl_tree<X> rotate_right(avl_tree<X> z) {
                    if (z == nullptr) return nullptr;
                    
                    avl_tree<X> y = z->Right;
                    if (y == nullptr) return nullptr;
                    
                    return std::shared_ptr<node<X>>(std::make_shared(node<X>(
                        y->Key, y->Value, 0, 
                        std::shared_ptr<node<X>>(std::make_shared(node<X>(
                            z->Key, z->Value, 
                            y->Meta.Balance > 0 ? -1 : 0,
                            z->Right, y->Left))),
                        y->Right)));
                }
            
                enum direction : uint8_t {
                    none = 0,
                    left = 1,
                    right = 2
                };

                template <typename X>
                avl_tree<X> rebalance(
                    avl_tree<X> t, 
                    const direction last, 
                    const direction next_to_last) {
                    if (last == none || next_to_last == none || balanced(t->Meta)) return t;

                    // todo
                    throw 0;
                }
            
                template <typename X>
                struct insert_return {
                    avl_tree<X> Tree;
                    const direction Last;

                    insert_return(
                        avl_tree<X> t,
                        const direction last) : Tree(t), Last(last) {}
                };
            
                template <typename X>
                insert_return<X> insert(avl_tree<X> t, X x) {
                    if (t == nullptr) return {
                        std::shared_ptr<node<X>>(std::make_shared(node<X>(x, 0))),
                        none};

                    if (k == t->Key) return {
                        std::shared_ptr<node<X>>(std::make_shared(node<X>(x, t->Meta, t->Left, t->Right))), 
                        none};

                    direction last = k < t->Key ? left : right;
                    insert_return<X> previous = last == left ? insert(t->Left, x) : insert(t->Right, x);
                    bool deeper = (last == left ? t->Left == nullptr : t->Right == nullptr) ||
                        (0 == (last == left ? t->Left->Meta : t->Right->Meta) && 0 != previous.Tree->Meta);
                    return {rebalance(
                        last == left ? 
                        std::shared_ptr<node<X>>(std::make_shared(node<X>(
                            t->Key, t->Value, 0, 
                            previous.Tree, t->Right)))
                        : std::shared_ptr<node<X>>(std::make_shared(node<X>(
                            t->Key, t->Value, 0, 
                            t->Left, previous.Tree))), last, previous.Last), last};
                }
                
            }

        }
    
    }

    template<typename X>
    bool valid(data::avl_tree<X> t) {
        return data::trees::avl::valid(t).Valid;
    }
    
}

