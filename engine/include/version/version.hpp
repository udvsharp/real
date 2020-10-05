// Copyright (c) 2020 udv. All rights reserved.

/*
 * This file contains all necessary headers
 * to develop applications using version.
 */

#ifndef VN
#define VN

//region core modules
#include "version/core.hpp"
#include "version/application.hpp"
#include "version/logger.hpp"
#include "version/event.hpp"
#include "version/window.hpp"
#include "version/keycode.hpp"
#include "version/input.hpp"
#include "version/layer.hpp"
#include "version/layer_stack.hpp"
#include "version/renderer.hpp"
#include "version/time.hpp"
//endregion

#ifdef VN_CLIENT
// region Entry point
int main (int argc, char** argv) {
	vn::logger::init();

	auto* app = vn::create();
	app->init();
	app->run();

	return 0;
}
// endregion
#endif

#undef VN_CORE_ERROR

#endif //VN
