#ifndef ABSTRACTIONS_COULD_HPP
#define ABSTRACTIONS_COULD_HPP

#include<abstractions.hpp>

namespace abstractions 
{
    // redeem contains function related to redeeming outputs
    // and creating transactions. 
    namespace redeem
    {
        // In order to redeem a bitcoin transaction, we must
        // have an idea about what the script of an output
        // could be. This is my default categorization.
        typedef ℕ essence;
        
        essence ignorance                   = 0;
        
        // We don't do anything with coinbase transactions, but
        // it is worth thinking about. 
        essence coinbase                    = 1; 
            
        // These are some basic transaction types... or are they?
        essence pay_to_public_key           = 1 << 1;
        essence pay_to_address              = 1 << 2;
        essence pay_to_multisig             = 1 << 3;
            
        // pay to script hash versions of the previous three. 
        essence public_key_pay_to_script    = 1 << 4;
        essence address_pay_to_script       = 1 << 5;
        essence multisig_pay_to_script      = 1 << 6;
            
        // There is something very interesting about this set of
        // categories. And that is, that we presume to
        // distinguish cases which are identical to all outward
        // appearance because all pay to hash outputs look the
        // same in the blockchain. 
        
        // This categorization does not cover every possible
        // bitcoin transaction. I would argue that it is only
        // necessary to think about redeeming outputs if we
        // know how to invert a kind of function because that
        // is what must be done in order to redeem an output.
        // Thus, if the categorization actually did cover every
        // possible transaction, that this would imply that we
        // had something to say on the inversion of all
        // computable functions.  
        // 
        // Instead, essence is a finite list of known cases
        // from a list that will never be exhausted in principle.
        // 
        // If other categories of transactions were to exist,
        // then a running wallet shouldn't think about whether
        // anything can be done with them. Thus, the set of
        // categories of interactions consist of those which
        // we understand.
        //
        // The unknown category exists by virtue of the fact
        // that this list can be extended in future versions of
        // this library. 
        
        // multisig is a description of how to interact with other
        // people which abstracts away the question of whether we
        // are going to use pay to script hash. 
        essence multisig = pay_to_multisig | multisig_pay_to_script;
        
        // redeeming a bitcoin transaction may require more 
        // than our own agency. Thus, there is a requirement
        // for categories concerning what will be accomplished
        // by the end of a series of actions that we could take.
        typedef ℕ accomplishment;
        
        accomplishment none                  = 0;
        accomplishment redeemed              = 1; 
            
        // can happen if we've got a multisig output and we can
        // add our signature such that fewer signatures are 
        // required before it has been redeemed. 
        accomplishment intermediate = 2;

        // things we could do to an input script. 
        // not a complete implementation of the primitive
        // recursive functions but you could imagine that such
        // a thing could exist. 
        typedef ℕ action;
        
        action identity = 1;
        action constant = 2;
        action successor = 3;
            
        // This is a possible category which is not required
        // in practice by my essences. You could probably 
        // just do something with this and become a billionare
        // without a clear explanation about what's valuable
        // about it at all. 
        action recurse = 4;
        
        // How much data do we have in relation to how much we want?
        // should be disjoint because we will want to be able to
        // form sums and products of them with ^ and 
        typedef ℕ proposition; 
        
        proposition impossible             = 0;
        proposition have_none              = 1 << 0; 
        proposition have_all               = 1 << 1; 
        proposition have_some_but_not_all  = 1 << 2;
            
        // you can look into the output script, so hypothetically 
        // there could be qualitative categories here. 
            
        // You know what I mean? There could be something like
            
        //     doing_better_in_category_A_than_in_category_B 
            
        // whatever that means.
        
        // we could think about who we are passing it to, but I 
        // would argue that we shouldn't have to. For most real
        // cases, you would simply be passing the transaction to
        // yourself because you hold all required keys. 
        
        // higher-level interactions should be built out higher
        // level code. 
        
        // that such thought should take place in 
        // a context which is using this library to construct
        // more complicated protocols at a higher level. This
        // library concerns one instance of the series of actions
        // which you take without communicting to anyone else
        
        // however, for most real cases, you would simply be passing
        // the transaction to yourself because you hold all required
        // keys. 

        // This library may be applicable to many coins, even though
        // there is not category for coin type. I would argue that
        // there is no need for any further categories and anything
        // different about using a given coin that is relevant to
        // this library could be represented as more cases in the 
        // existing categories or as different implementations of
        // this library. 
        
        // we now declare the could() function. 
        //
        // could() is a function which says whether for a given
        // essence, and for a given accomplishment that we wish to
        // achive, have we achived it if the given proposition about
        // the input that is used to transform some future transaction
        // is true if I were to perform the given action upon the
        // transaction.
        // 
        // Since could() controls the behavior of a wallet in a
        // high-level way, it is important for its behavior to be
        // both comprehensible and reliable. 
        constexpr const bool could(
            
            // The category of interaction.
            essence nature,
            
            // What might have happened during the course 
            // of a potential redemption operation?
            accomplishment why,
            
            // the specific actions which we might take
            // with regard to a 
            action how,
            
            // The last input to the could function is a
            // description of what is evidently true to us
            // alone because the proof of the proprosition may
            // involve both public and private knowledge which
            // we want to stay private. 
            proposition what
        );
        
        // When we are redeeming a tx, we have a goal and we want
        // to think about what are the properties of events in the
        // past that might have resulted in us remembering them
        // for later. 
        
        // Thus, what we really want is the would() function. 
        constexpr const proposition would(
            const accomplishment what
        );
        
        // The would() function partly inverts the could() function. 
        
        // How do we make it? Well there is another function we
        // might want called remember, and that is the function that
        // tells us if we want to remember a given observation.
        
        constexpr const bool remember(
            proposition observation, 
            const accomplishment what
        );
        
        // if we had the remember() function, we could define the 
        // would() function like so. 
        
        constexpr const proposition would(
            const accomplishment what
        ) {
            const bool r1 = remember(have_none, what);
            const bool r2 = remember(have_all, what);
            const bool r3 = remember(have_some_but_not_all, what);
            
            return (((r1 && have_none) * all) | have_none) ^
                (((r2 && have_all) * all) | have_all) ^ 
                (((r3 && have_some_but_not_all) * all) | have_some_but_not_all);
        }
        
        // Normally we have an observation and want to know what
        // available actions we can take and what they might do. 
        
        // That would be the can() function. 
        constexpr const bool can(
            proposition observation, 
            action how,
            accomplishment what
        );
        
        // if we had the can() function, we could define the remember
        // function like so. This says if we can do anything to
        // accomplish the given accomplishment, then we should
        // remember the given observation. 
        
        constexpr const bool remember(
            proposition observation, 
            accomplishment what
        ) {
            // We do not worry about recurse because we don't know
            // what we can do with it. 
            return
                can(observation, constant, what) &&
                can(observation, successor, what) &&
                can(observation, identity, what);
        }
        
        // but we can define the can function! It is
        // simply an iteration over the conceptual categories.
        constexpr const bool can(
            proposition observation, 
            action how,
            accomplishment what
        ) {
            return
                could(pay_to_address, what, how, observation) && 
                could(address_pay_to_script, what, how, observation) && 
                could(pay_to_multisig, what, how, observation) && 
                could(multisig_pay_to_script, what, how, observation) &&
                could(pay_to_public_key, what, how, observation) && 
                could(public_key_pay_to_script, what, how, observation) && 
                could(coinbase, what, how, observation);
        }
        
        // And what is could()? 
        constexpr const bool could(
            essence nature,         // formal cause
            accomplishment why,     // final cause
            action how,             // efficient cause
            proposition what        // material cause
        ) {            
            return
                // You are always allowed to do nothing if you don't want
                // to accomplish anything.
                (why == none) && (how == identity) || 
                    (why != none) && 
        
                // If you have no data, then only the coinbase would give
                // us any achievement other than nothing, since the coinbase 
                // can be redeemed without acting upon anything. 
                (what == have_none) && (nature == coinbase) ||
                    (what != have_none) && 
            
                // if this is a multisig case, then prepend is the only
                // possible successful action, given that we already know
                // that we want to accomplish something. Doing so would
                // necessarily achieve intermediate progress regardless
                // of whether the transaction was redeemed. 
                ((multisig ^ nature) != ignorance) && (how == successor) &&
                    ((why == intermediate) || (what == have_all)) ||
                    ((multisig ^ nature) == ignorance) &&
            
                // Otherwise, it is either a coinbase, which means it is
                // successful, or it is something for which we have all data
                // and we plan to replace all the data that will be given
                // in some future transaction input and we want to redeem
                // the transaction completely.
                // 
                // We do not know any other cases in which we do not have
                // all required information or for which the initial input
                // of a future tx might be relevant to how we redeem it or
                // for which we know of any possible intermediate outcome. 
                ((what == have_all && constant == how && redeemed == why)
                    || coinbase == nature);
                
                // If future people come to rely very heavily on whatever
                // evolves out of this function, it is very important that
                // all statements in it are justified by reason and by the
                // free choice who ever designed the scema of essences. This
                // function tells your computer how to think. It must be
                // in accordance with the user's will.
        }
    }

}

#endif 
