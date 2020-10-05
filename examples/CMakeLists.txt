message(STATUS "Configuring examples")

### Sandbox
if (OPTION_REAL_BUILD_SANDBOX)
	add_subdirectory(sandbox)
endif ()