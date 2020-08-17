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

		include/version/event.hpp
		include/version/event/base_event.hpp
		include/version/event/key_event.hpp
		include/version/event/mouse_event.hpp
		include/version/event/window_event.hpp
		include/version/layer.hpp)

target_include_directories(
		${VN_LIBRARY_TARGET_NAME}
		PUBLIC
		"include"
		"${CMAKE_CURRENT_BINARY_DIR}"
		PRIVATE
		"src"
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
# Separate Files
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

# Modify Sources
file(READ "${CMAKE_CURRENT_BINARY_DIR}/${META_VN_PROJECT_NAME}/core-export.hpp" VN_CMAKE_EXPORT_CONTENTS)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/${META_VN_PROJECT_NAME}/core-compiler.hpp" VN_CMAKE_COMPILERS_CONTENTS)