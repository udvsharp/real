// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_IMGUI_LAYER
#define VN_IMGUI_LAYER

#include "version/core.hpp"
#include "version/layer/base_layer.hpp"

namespace vn {
    class VN_API imgui_layer : public layer {
    public:
        imgui_layer();
        ~imgui_layer();

        void attach() override;
        void detach() override;
        void update() override;
        void handle_event(ev &ev) override;
    };
}

#endif //VN_IMGUI_LAYER
