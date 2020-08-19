message(STATUS "Configuring ${META_VN_NAME_VERSION}")

# Target
add_library(
		${VN_LIBRARY_TARGET_NAME}
		SHARED  # It is necessary

		include/version/util/singleton.hpp

		include/version/version.hpp
		include/version/core.hpp

		include/version/application.hpp
		src/application.cpp

		include/version/logger.hpp
		src/logger.cpp

		include/version/layer.hpp
		include/version/layer_stack.hpp
		include/version/layer/base_layer.hpp
		src/base_layer.cpp
		src/layer_stack.cpp

		include/version/event.hpp
		include/version/event/base_event.hpp
		include/version/event/key_event.hpp
		include/version/event/mouse_event.hpp
		include/version/event/window_event.hpp
)

target_include_directories(
		${VN_LIBRARY_TARGET_NAME}
		PUBLIC
		"include"
		"${CMAKE_CURRENT_BINARY_DIR}"
		PRIVATE
		"src"
)

target_precompile_headers(
		${VN_LIBRARY_TARGET_NAME}
		PRIVATE
		<utility>
		<functional>

		<iostream>

		<vector>
		<map>
		<string>
		<set>
)

# Properties
set_target_properties(
		${VN_LIBRARY_TARGET_NAME} PROPERTIES

		# Version
		VERSION ${META_VN_VERSION}
		SOVERSION ${META_VN_VERSION_MAJOR}

		# C++
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF

		# C
		C_STANDARD 11
		C_STANDARD_REQUIRED ON
		C_EXTENSIONS OFF
)

target_compile_definitions(
		${VN_LIBRARY_TARGET_NAME}
		PRIVATE

		PUBLIC
		# Build type macros
		$<$<CONFIG:Debug>:VN_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:VN_DEBUG>
		$<$<CONFIG:Release>:VN_RELEASE>
		$<$<CONFIG:Dist>:VN_DIST>
		INTERFACE
		VN_CLIENT
)

set_target_properties(
		${VN_LIBRARY_TARGET_NAME} PROPERTIES

		VISIBILITY_INLINES_HIDDEN YES
		CXX_VISIBILITY_PRESET hidden
		C_VISIBILITY_PRESET hidden
		ASM_VISIBILITY_PRESET hidden
)

# Utility
# Generated Files
write_compiler_detection_header(
		FILE "${META_VN_PROJECT_NAME}/core-compiler.hpp"
		PREFIX ${META_VN_PROJECT_NAME_PREFIX}
		COMPILERS MSVC GNU
		FEATURES cxx_override
)

generate_export_header(
		${VN_LIBRARY_TARGET_NAME}
		BASE_NAME "${META_VN_PROJECT_NAME_PREFIX}"
		PREFIX_NAME "${META_VN_PROJECT_NAME_PREFIX}_"
		INCLUDE_GUARD_NAME "${META_VN_PROJECT_NAME_PREFIX}_CORE_COMPILER"
		EXPORT_MACRO_NAME "API"
		EXPORT_FILE_NAME "${META_VN_PROJECT_NAME}/core-export.hpp"
		NO_EXPORT_MACRO_NAME "NO_EXPORT"
		DEPRECATED_MACRO_NAME "DEPRECATED"
		INCLUDE_GUARD_NAME "${META_VN_PROJECT_NAME_PREFIX}_CORE_API"
		STATIC_DEFINE "STATIC"
		NO_DEPRECATED_MACRO_NAME "NO_DEPRECATED"

		# DEFINE_NO_DEPRECATED
)

# Custom commands
set(LOGS_DIR "${CMAKE_CURRENT_BINARY_DIR}/logs")
set(LOG_EXPORTS_FILE "${LOGS_DIR}/exports.txt")

file(MAKE_DIRECTORY "${LOGS_DIR}")

# TODO: add support for other platforms
if (WIN32)
	add_custom_command(
			TARGET ${VN_LIBRARY_TARGET_NAME} POST_BUILD
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Saving DLL file exports"
			BYPRODUCTS "${LOG_EXPORTS_FILE}"

			COMMAND dumpbin /exports $<TARGET_FILE:${VN_LIBRARY_TARGET_NAME}> > "${LOG_EXPORTS_FILE}"

			VERBATIM
	)
endif ()