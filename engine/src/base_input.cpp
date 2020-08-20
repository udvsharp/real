// Copyright (c) 2020 udv. All rights reserved.

#include "version/input.hpp"

namespace vn {
    input *input::make() {
        input *input;

#ifdef VN_PLATFORM_WINDOWS
        input = new platform::input{};
#endif
        return input;
    }
}
