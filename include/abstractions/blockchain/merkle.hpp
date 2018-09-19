#ifndef ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP
#define ABSTRACTIONS_BLOCKCHAIN_MERKLE_HPP

#include <abstractions/abstractions.hpp>
#include <abstractions/data.hpp>

namespace abstractions
{
        
    namespace merkle
    {
        
        template <typename digest>
        struct proof {
            struct step {
                const pointer<step> Parent;
                const digest Left;
                const digest Right;
                
                step(pointer<step> p, digest l, digest r) : Parent(p), Left(l), Right(r) {}
            };
        
            using steps = list<step>;
            
            using combine = digest (*const)(digest, digest);
            
            const digest Initial;
            
            const steps Steps;
            
            static bool verify(combine c, steps next, digest init, digest fine) {
                if (next == nullptr) return init == fine;
                    
                if (init != next->Left && init != next->Right) return false;
                    
                return verify(c, next->Next, c(next->Left, next->Right), fine);
            }
            
            inline static bool verify(combine c, proof p, digest fine) {                    
                return verify(c, p.Steps, p.Initial, fine);
            }
            
            proof(digest i, steps s) : Initial(i), Steps(s) {}
            proof() {}
        };
        
        template <typename digest>
        struct proofs : private map<digest, list<proof<digest>>> {
            using combine = typename proof<digest>::combine;
            
            const combine Combine;
            
            const list<proof<digest>> operator[](digest d) const {
                return map<digest, list<proof<digest>>>::operator[](d);
            }
            
            const proofs add(proof<digest> p, digest i, digest root) const {
                if (!verify(Combine, p, i, root)) return this;
                
                return proofs(map<digest, list<proof<digest>>>::replace(root, this->operator[](root) + entry(p, i)), Combine);
            }
            
            bool valid() const {
                for (digest d : static_cast<map<digest, list<proof<digest>>>>(this)) 
                    if (!proof<digest>::verify(Combine, this->operator[](d), d)) return false;
                    
                return true;
            }
            
            proofs(combine c) : map<digest, list<proof<digest>>>(), Combine(c) {}

        private:            
            proofs(map<digest, list<proof<digest>>> p, combine c) : map<digest, list<proof<digest>>>(p), Combine(c) {}
        };
        
    }

}

#endif
