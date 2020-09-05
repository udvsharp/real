message(STATUS "Configuring examples")

### Sandbox
if (OPTION_VN_BUILD_SANDBOX)
	add_subdirectory(sandbox)
endif ()