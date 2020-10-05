// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_IMGUI
#define REAL_LAYER_IMGUI

#include "real/core.hpp"
#include "real/layer/base_layer.hpp"

namespace real {
    class REAL_API imgui_layer : public layer {
    public:
        imgui_layer();
        ~imgui_layer();

        void attach() override;
        void detach() override;
        void update(timestep ts) override;
        void handle_event(ev &ev) override;
    };
}

#endif //REAL_LAYER_IMGUI
