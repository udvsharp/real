// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_IMGUI
#define REAL_LAYER_IMGUI

#include "real/core.hpp"
#include "real/layer/base_layer.hpp"

namespace Real {
	class REAL_API ImGUILayer : public Layer {
	public:
		ImGUILayer();
		~ImGUILayer();

		void Attach() override;
		void Detach() override;
		void Update(Timestep ts) override;
		void HandleEvent(Event &ev) override;
	};
}

#endif //REAL_LAYER_IMGUI
