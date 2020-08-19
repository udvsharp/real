// Copyright (c) 2020 udv. All rights reserved.

#include <version/version.hpp>

class application : public vn::application {
public:
	application() {
		layers().push_layer(new vn::layer());
	}

	virtual void tick() override {
		VN_TRACE("TICK");
	}
};

vn::application *vn::create() {
	VN_TRACE("Creating application...");
	return new ::application();
}