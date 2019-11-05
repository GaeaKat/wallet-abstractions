// Copyright (c) 2018-2019 Katrina Swales
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <abstractions/timechain/output.hpp>

namespace abstractions::timechain::output {

    const bytes_view serialized::script() const {
        throw data::method::unimplemented{};
    }

    satoshi serialized::value() const {
        throw data::method::unimplemented{};
    }

}