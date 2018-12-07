#ifndef ABSTRACTIONS_MACHINE_HPP
#define ABSTRACTIONS_MACHINE_HPP

#include <abstractions/list.hpp>

namespace abstractions
{
    
    namespace machine 
    {
        
        namespace definition {
            
            template <typename M>
            struct initializeable_without_transaction {
                M initialize() {
                    return M{};
                }
            };
            
            template <typename M, typename Tx>
            struct initializeable : initializeable_without_transaction<M> {
                M initialize(Tx t) {
                    return M{t};
                }
            };
            
            template <typename M, typename script>
            struct machine {
                M run(M m, script s) {
                    return m << s;
                }
                
                bool valid_state(M m) {
                    return m.valid_state();
                }
            };
            
        }
        
    }
    
}

#endif

