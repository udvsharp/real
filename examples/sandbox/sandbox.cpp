// Copyright (c) 2020 udv. All rights reserved.

#include <version/version.hpp>

class application : public vn::application {
public:
	virtual void run() override {
	}
};

vn::application *vn::create() {
	return new ::application();
}