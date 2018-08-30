#ifndef ABSTRACTIONS_DATABASE_HPP
#define ABSTRACTIONS_DATABASE_HPP

namespace abstractions
{

    template<typename tag>
    struct memory {
        virtual bool exists(tag) const = 0;
    };
        
    template <typename K>
    struct entry {
        bool Exists;
        K Value;
            
        entry() : Exists(false), Value() {}
        entry(K k) : Exists(true), Value(k) {}
    };

    template<typename K, typename tag>
    struct database : public memory<tag> {
        virtual entry<K> get(tag) const = 0;
            
        bool exists(tag t) const final override {
            return get(t).Exists;
        };
    };

}

#endif
