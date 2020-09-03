message(STATUS "Configuring ${META_VN_NAME_VERSION}")

# Target
add_library(
		${VN_LIBRARY_TARGET_NAME}
		SHARED  # It is necessary

		### Headers
		# util
		include/version/util/singleton.hpp
		# Core
		include/version/version.hpp
		include/version/core.hpp
		include/version/application.hpp
		include/version/logger.hpp
		include/version/layer.hpp
		include/version/layer_stack.hpp
		include/version/input.hpp
		include/version/window.hpp
		include/version/event.hpp
		# Layers
		include/version/layer/base_layer.hpp
		include/version/layer/imgui_layer.hpp
		# Window
		include/version/window/base_window.hpp
		# Input
		include/version/keycode.hpp
		include/version/input/base_input.hpp
		# Events
		include/version/event/base_event.hpp
		include/version/event/key_event.hpp
		include/version/event/mouse_event.hpp
		include/version/event/window_event.hpp
		# Renderer
		include/version/renderer.hpp
		include/version/renderer/base_rendering_context.hpp
		include/version/renderer/base_renderer.hpp
		include/version/renderer/shader.hpp
		include/version/renderer/buffer_vertex.hpp
		include/version/renderer/buffer_index.hpp
		## Api
		## GL
		include/version/api/gl/gl_rendering_context.hpp
		include/version/api/gl/gl_buffer_vertex.hpp
		include/version/api/gl/gl_buffer_index.hpp

		### Sources
		# Core
		src/application.cpp
		src/base_window.cpp
		src/layer_stack.cpp
		src/logger.cpp
		# Layers
		src/base_layer.cpp
		src/layer/imgui_layer.cpp
		# Input
		src/base_input.cpp
		# Renderer
		src/renderer/base_rendering_context.cpp
		src/renderer/base_renderer.cpp
		src/renderer/buffer_vertex.cpp
		src/renderer/buffer_index.cpp
		src/renderer/shader.cpp
		## Api
		## GL
		# Imgui
		src/api/gl/imgui_impl_opengl3.h
		src/api/gl/imgui_impl_opengl3.cpp
		# Renderer
		src/api/gl/gl_rendering_context.cpp
		src/api/gl/gl_buffer_vertex.cpp
		src/api/gl/gl_buffer_index.cpp
)

# Platform-dependent sources
if (WIN32)
	target_sources(
			${VN_LIBRARY_TARGET_NAME}
			PUBLIC
			# Window
			include/version/platform/windows/windows_window.hpp
			# Input
			include/version/platform/windows/windows_input.hpp
			PRIVATE
			# Window
			src/platform/windows/windows_window.cpp
			# Input
			src/platform/windows/windows_input.cpp
	)
endif ()

# Shaders
set(
		SHADERS_SRCS
		include/version/renderer/shaders/base.vs.glsl
		include/version/renderer/shaders/base.fs.glsl
)

foreach (SHADER_SRC ${SHADERS_SRCS})
	get_filename_component(SHADER_FILENAME "${SHADER_SRC}" NAME)
	configure_file("${SHADER_SRC}" "${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_FILENAME}" COPYONLY)
	# TODO: fix build directories for msvc
	if (MSVC)
		configure_file("${SHADER_SRC}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/shaders/${SHADER_FILENAME}" COPYONLY)
		configure_file("${SHADER_SRC}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/shaders/${SHADER_FILENAME}" COPYONLY)
	else()
		configure_file("${SHADER_SRC}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/${SHADER_FILENAME}" COPYONLY)
	endif ()
endforeach ()

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

		# Platform-dependent headers
		$<$<PLATFORM_ID:Windows>:<Windows.h>>
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
		# Platform macros
		$<$<PLATFORM_ID:Windows>:VN_PLATFORM_WINDOWS>
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
set(LOG_GLFWINFO_FILE "${LOGS_DIR}/glfwinfo.txt")

file(MAKE_DIRECTORY "${LOGS_DIR}")

# TODO: add support for other platforms
if (WIN32)
	# Save DLL exports
	add_custom_command(
			TARGET ${VN_LIBRARY_TARGET_NAME} POST_BUILD
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Saving DLL file exports"
			BYPRODUCTS "${LOG_EXPORTS_FILE}"

			COMMAND dumpbin /exports $<TARGET_FILE:${VN_LIBRARY_TARGET_NAME}> > "${LOG_EXPORTS_FILE}"

			VERBATIM
	)
endif ()