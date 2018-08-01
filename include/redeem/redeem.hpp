#ifndef ABSTRACTIONS_REDEEM_HPP
#define ABSTRACTIONS_REDEEM_HPP

#include<redeem/could.hpp>

namespace abstractions 
{

    namespace redeem
    {        
        // Let's start with information that came to us from the 
        // outside world. 
        template<
        
            // I imagine Link is a connection in the blockchain.
            // It is an output and index to the output and it includes
            // the knowledge that this index points to the blockchain.
            typename Link, 
            
            // I imagine that an Outpoint is an index to a Link.
            typename Outpoint,
            
            // An output is a function in the blockchain, which we 
            // may know know to redeem! 
            typename Output>
        struct eyes {
            
            // From an outpoint, we can get a pointer to a 
            // Link. And we are going to dereference that pointer
            // if it is not nullptr, so you had better make sure 
            // that any pointer you give us which is not nullptr
            // had better be something that we can dereference!! 
            virtual Link const * prior(Outpoint) const = 0;

            // From a reference to a link, we can get an output. 
            // Thus, it is only possible to have an output if it
            // was given to us, or if an instance of Link can 
            // really be constructed somewhere, somehow in 
            // this program. It is up to the implementer to 
            // describe this type, beyond the requirement that 
            // this function cannot be called unless an instance
            // of that type actually exists somewhere else in the program.
            virtual Output output(Link&) const = 0;
            
            // from an output we cannot get an outpoint, so we cannot
            // go arbitrarily far back in the blockchain. 
            
            vector<Output> outputs(vector<Outpoint> outpoints) const
            {
                std::vector<Output> outs(outpoints.size());
                        
                for (int i = 0; i < outpoints.size(); i++)
                {
                    Link const * p = prior(outpoints[i]);
                    if (p == nullptr) return {};
                    outs[i] = saves(output(p));
                }
                        
                return outs;
            }

            virtual ℕ saves(Output) const = 0;
            
            ℕ saves(vector<Outpoint> outpoints) const
            {
                ℕ spent = 0;
                        
                for (Outpoint o : outpoints)
                {
                    Link const * p = prior(o);
                    if (p == nullptr) return ℵ0;
                    spent += saves(output(p));
                }
                        
                return spent;
            }
        };
        
        template<typename Goal, typename Magic, typename Outpoint>
        struct desire {
            virtual ℕ spend(Goal) const = 0;
        
            struct transformation
            {
                virtual const Magic operator()(Magic) const = 0;
            };
        
            struct input final
            {
                Outpoint outpoint;
                Magic magic;
                
                const input replace(Magic m) {
                    return {outpoint, m};
                }
                
                const input transform(const transformation& t) {
                    return {outpoint, t(magic)};
                }
            };

            // a possibility is something which gives us a transformation 
            // when provided with a vector of outputs and a desire. 
            struct possibility
            {
                virtual transformation operator()(vector<Outpoint>, Goal) const = 0;
                
                Magic initial;
                
                possibility() : Magic() {}
                possibility(Magic i) : Magic(i) {}
            };
        };

        template<
            typename Link,
            typename Outpoint,
            typename Output,
            typename Desire,
            typename Magic>
        struct will : 
            public eyes<Link, Outpoint, Output>,
            public desire<Desire, Magic, Outpoint>
        {
            typedef typename desire<Desire, Magic, Outpoint>::input input;
            
            struct transaction
            {
                vector<input> inputs;
                Desire desire;
            };
                
            bool positive(transaction t) const
            {
                int spendable = 0;
                for(input i : t.inputs) {
                    spendable += saves(i.outpoint);
                }
                    
                return spends(t.goal);
            }
            
            // This is a non-const function because it changes the state of the network. 
            virtual void send(transaction) = 0;
        };
        
        enum status {
            valid, 
            invalid, 
            open_minded
        };
    }
    
} // redeem

template<
    typename Link,
    typename Proposition,
    typename Action,
    typename Accomplishment,
    typename Outpoint,
    typename Output,
    typename Desire,
    typename Magic>
struct redeemer : 
    public redeem::thought<Link, Proposition, Action, Accomplishment>, 
    public redeem::body<Link, Outpoint, Output, Desire, Magic>
{
};

}

#endif
