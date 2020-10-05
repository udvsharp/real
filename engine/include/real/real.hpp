// Copyright (c) 2020 udv. All rights reserved.

/*
 * This file contains all necessary headers
 * to develop applications using version.
 */

#ifndef VN
#define VN

//region core modules
#include "real/core.hpp"
#include "real/application.hpp"
#include "real/logger.hpp"
#include "real/event.hpp"
#include "real/window.hpp"
#include "real/keycode.hpp"
#include "real/input.hpp"
#include "real/layer.hpp"
#include "real/layer_stack.hpp"
#include "real/renderer.hpp"
#include "real/time.hpp"
//endregion

#ifdef REAL_CLIENT
// region Entry point
int main (int argc, char** argv) {
	real::logger::init();

	auto* app = real::create();
	app->init();
	app->run();

	return 0;
}
// endregion
#endif

#undef REAL_CORE_ERROR

#endif //VN
