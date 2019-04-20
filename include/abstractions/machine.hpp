#ifndef ABSTRACTIONS_MACHINE
#define ABSTRACTIONS_MACHINE

namespace abstractions {
    
    namespace machine {
    
        // template specialize this if you have a different
        // definition of how the machine is run. 
        template <typename interpreter, typename script, typename tx>
        struct run {
            bool operator()(interpreter m, script output, script input, tx transaction) const {
                return m.run(output, input, transaction);
            }
        };
    
        template <typename interpreter, typename script, typename tx>
        struct definition {
            bool run(interpreter m, script output, script input, tx transaction) const {
                return machine::run<interpreter, script, tx>{}(m, output, input, transaction);
            }
        };
    
    }

}

#endif

