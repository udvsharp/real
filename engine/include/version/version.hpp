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
//endregion

#ifdef VN_CLIENT
// region Entry point
int main (int argc, char** argv) {
	auto* app = vn::create();
	app->run();

	return 0;
}
// endregion
#endif

#endif //VN
