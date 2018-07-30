#ifndef #REDEEM_REDEEM_HPP
#define #REDEEM_REDEEM_HPP

#include<vector>

namespace abstractions 
{

namespace redeem
{
    
template<typename X>
using vector = std::vector<X>;

// Things we can do to inputs corresponding to a given output. 
enum action {
    none = 0, 
    add_signature_to_multisig = 1, 
    redeem = 2
};

// transformation is an operation that is applied to an input script. 
template<typename Script>
struct transformation {
    virtual Script operator()(Script) = 0;
};

// a possibility is something which, when given a transaction, gives us a transformation. 
template<typename Transaction, typename Script>
struct possibility {
    virtual transformation<Script> operator()(Transaction) = 0;
    
    Script Initial;
};

// These are the axioms of my theory. 
template<
    typename Goal,          // Transaction without any inputs. 
    typename Link,          // An output combined with an outpoint (ie an output that's in the blockchain)
    typename Transaction,   // A transaction, possibly not yet fully redeemed. 
    typename Outpoint,      // An index in the blockchain. 
    typename Output,        // an input (Outpoint + Script
    typename Script,        // Something that redeems an output. 
    typename Input>         // An output (Link - Outpoint)
struct axioms {
    // A link is just an output and and outpoint put together, so we can get both from a Link.
    virtual Outpoint outpoint(Link) = 0;
    virtual Output output(Link) = 0;
    
    // We can get a possibility from a Link and an action. 
    virtual possibility<Transaction, Script> can_do(Link, action) = 0;
    
    // From an outpoint and Script, we can make an input. 
    virtual Input input(Outpoint, Script) = 0;
    
    virtual Transaction replace(Transaction, Outpoint, Script) = 0;
    
    // A transaction is a goal plus inputs. (Therefore, a Goal is a transaction without inputs)
    virtual Transaction tx(Goal, vector<Input>);
};

template<typename Goal, typename Link, typename Transaction, typename Outpoint, typename Output, typename Script, typename Input>
Transaction sign(axioms<Goal, Link, Transaction, Outpoint, Output, Script, Input> go, possibility<Transaction, Script> sign, Transaction t, Outpoint op) {
    Script in = go.output(t, op);
    
    if (in == Script()) {
        return Transaction();
    }
    
    go.replace(t, op, sign(t)(in));
}

}

}

#endif
