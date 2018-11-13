#ifndef ABSTRACTIONS_OPTIONAL_HPP
#define ABSTRACTIONS_OPTIONAL_HPP

namespace abstractions {

    template <typename X>
    struct optional {
        bool Exists;
        X Value;
        
        optional() : Exists(false), Value{} {}
        optional(X x) : Exists(true), Value(x) {}
        
        optional(const optional<X>& o) : Exists(o.Exists), Value(o.Value) {}
        
        bool valid(bool (*v)(X)) {
            return (!Exists) || v(Value);
        }
    };

}

#endif
