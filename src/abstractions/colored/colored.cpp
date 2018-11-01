
#include <abstractions/colored/colored.hpp>

namespace abstractions
{

    namespace colored
    {
        
        template <typename tx, typename point, typename C> 
        struct curry {
            const blockchain<tx, point, C>& Blockchain;
            
            const value<C> operator()(point p) const {
                return Blockchain.value(p);
            }
        };
        
        template <typename C>
        inline value<C> get_value(data::maps::entry<N, value<C>> e) {
            return e.Value;
        }
        
        template <typename tx, typename point, typename C> 
        bool verify(const blockchain<tx, point, C>& b, meta<C> m) {
            switch (m.Type) {
                default:
                case none:
                    return false;
                case genesis:
                    return true;
                case mint:
                    for (point p : m.Inputs) if (!verify(b, p)) return false;
                    return true;
                case send:
                    return reduce(curry<tx, point, C>(b), plus, m.Inputs) <= reduce(get_value, plus, m.Outputs);
            }
        }
        
    }

}
